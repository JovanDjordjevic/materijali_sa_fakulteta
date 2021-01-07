/* Napisati program koji kao argumente komandne linije prima putanje do 
 * FIFO fajlova. Program istovremeno za sve fajlove ceka na dogadjaj da 
 * je kroz neki FIFO stigao podatak koriscenjem poll interfejsa. Kroz 
 * FIFO fajlove pristizu samo celi brojevi, cita se sve dok se ne zatvore 
 * svi FIFO fajlovi na strani koja pise u FIFO. Na standardni izlaz ispisati 
 * maksimalnu sumu brojeva koji se nalaze u jednom FIFO fajlu i naziv tog 
 * FIFO fajla (ne putanju nego NAZIV).
 * 
 * Zadatak je uradjen upotrebom epoll interfejsa.
 */ 
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/epoll.h>
#include <string.h>

#define check_error(expr, userMsg)\
	do {\
		if (!(expr)) {\
			perror(userMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while (0)
	
/* uvodimo novi tip koji opisuje podatke koje
 * prosledjujemo uz svaki fajl deskriptor 
 * epoll instanci
 */ 
typedef struct {
	
	FILE* f;
	char* name;
	int localSum;
	
} epollData_t;	

int main(int argc, char** argv) {
	
	check_error(argc > 1, "...");
	
	/* kreiramo epoll instancu */
	int nfd = argc-1;
	int epollFd = epoll_create(nfd);
	
	/* alociramo prostor za argumente koje saljemo kroz epoll */
	epollData_t* args = malloc(sizeof(epollData_t)*nfd);
	check_error(args != NULL, "...");
	
	/* u petlji dodajemo jedan po jedan fajl deskriptor epoll instanci */
	struct epoll_event currEvent;
	for (int i = 0; i < nfd; i++) {
		
		/* otvaramo fajl deskriptor - obavezno kao O_NONBLOCK */
		int fd = open(argv[i+1], O_RDONLY | O_NONBLOCK);
		check_error(fd != -1, "...");
		
		/* inicijalizujemo podatke
		 * prvo otvaramo fajl strim
		 */ 
		args[i].f = fdopen(fd, "r");
		check_error(args[i].f != NULL, "...");
		/* pamtimo ime fajla */
		args[i].name = argv[i+1];
		/* inicijalizujemo lokalnu sumu na 0 */
		args[i].localSum = 0;
		
		/* definisemo koje aktivnosti pratimo na fajl deskriptoru */
		currEvent.events = EPOLLIN | EPOLLERR | EPOLLHUP;
		/* pamtimo adresu argumenta koji cemo da zakacimo uz fajl deskriptor */
		currEvent.data.ptr = (void*)&args[i];
		
		/* dodajemo fajl deskriptor epoll instanci */
		check_error(epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &currEvent) != -1, "....");
	}
	
	/* niz struktura u koje ce epoll upisati one na kojima se nesto desilo */
	struct epoll_event activeFds[10];
	/* u petlji */
	while (nfd) {
		
		/* cekamo da se nesto desi */
		int retVal = epoll_wait(epollFd, activeFds, 10, -1);
		check_error(retVal != -1, "....");
		
		/* prolazimo kroz niz aktiviranih fajl deskriptora */
		for (int i = 0; i < retVal; i++) {
			
			/* ako je fajl deskriptor spreman za citanje */
			if (activeFds[i].events & EPOLLIN) {
				
				/* dohvatamo podatke koji su prikaceni uz fajl deskriptor */
				epollData_t* data=(epollData_t*)activeFds[i].data.ptr;
				/* citamo brojeve sve do kraja */
				int x;
				while (fscanf(data->f, "%d", &x) == 1) {
					
					data->localSum += x;
				}
				/* provera gresaka */
				check_error(feof(data->f),"...");
			}
			/* ako se desila greska ili ako je druga strana zatvorila svoj kraj */
			else if (activeFds[i].events & (EPOLLERR | EPOLLHUP)) {
				
				/* dohvatamo podatke koji su prikaceni uz fajl deskriptor */ 
				epollData_t* data = (epollData_t*)activeFds[i].data.ptr;
				/* zatvaramo fajl strim */
				fclose(data->f);
				/* umanjujemo brojac otvorenih fajlova */
				nfd--;
			}
		}
	}
	
	/* trenutni max */
	int max = args[0].localSum;
	/* ime fajla u kome je pronadjen trenutani max */
	char* maxName = args[0].name;
	for (int i = 1; i < nfd; i++) {
		
		if (args[i].localSum > max) {
			
			max = args[i].localSum;
			maxName = args[i].name;
		}
	}
	
	/* stampamo ime fajla i max */
	char* name = strrchr(maxName, '/');
	printf("%d %s\n", max, name != NULL ? name : maxName);
	
	/* oslobadjamo resurse */
	free(args);
	
	/* zatvaramo epoll instancu */
	close(epollFd);	
	
	exit(EXIT_SUCCESS);
}
			
