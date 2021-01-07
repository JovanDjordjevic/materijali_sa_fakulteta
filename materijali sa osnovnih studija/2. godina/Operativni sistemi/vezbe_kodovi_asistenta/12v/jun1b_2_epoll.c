/* Napisati program koji kao argumente komandne linije prima putanje do 
 * FIFO fajlova. Program istovremeno za sve fajlove ceka na dogadjaj da 
 * je kroz neki FIFO stigao podatak koriscenjem poll interfejsa. Kroz 
 * FIFO fajlove pristizu samo celi brojevi, cita se sve dok se ne zatvore 
 * svi FIFO fajlovi na strani koja pise u FIFO. Na standardni izlaz ispisati 
 * maksimalni procitan broj i naziv FIFO fajla (ne putanju nego NAZIV).
 * 
 * Resenje sa epoll-om.
 */ 
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/epoll.h>

#define check_error(expr, userMsg)\
	do { \
		if (!(expr)) {\
			perror(userMsg);\
			exit(EXIT_FAILURE); \
		}\
	} while (0)

/* uvodimo novi tip koji opisuje podatke koje
 * prosledjujemo uz svaki fajl deskriptor 
 * epoll instanci
 */ 
typedef struct {
	
	FILE* f;
	char* name;
	
} epollData_t;

int main(int argc, char** argv) {
	
	check_error(argc > 1, "....");
	
	/* kreiramo epoll instancu */
	int nfd = argc-1;
	int epollFd = epoll_create(nfd);
	
	/* u petlji dodajemo jedan po jedan fajl deskriptor epoll instanci */
	struct epoll_event currEvent;
	for (int i = 0; i < nfd; i++) {
		
		/* otvaramo fajl deskriptor - obavezno kao O_NONBLOCK */
		int fd = open(argv[i+1], O_RDONLY | O_NONBLOCK);
		check_error(fd != -1, "...");
		
		/* alociramo memoriju za podatke koje pridruzjemo fajl deskriptoru */
		epollData_t* arg = malloc(sizeof(epollData_t));
		check_error(arg != NULL, "...");
		
		/* inicijalizujemo podatke
		 * prvo otvaramo fajl strim
		 */ 
		arg->f = fdopen(fd, "r");
		check_error(arg->f != NULL, "...");
		/* pamtimo ime fajla */
		arg->name = argv[i+1];
		
		/* definisemo koje aktivnosti pratimo na fajl deskriptoru */
		currEvent.events = EPOLLIN | EPOLLERR | EPOLLHUP;
		/* pamtimo adresu argumenta koji cemo da zakacimo uz fajl deskriptor */
		currEvent.data.ptr = (void*)arg;
		
		/* dodajemo fajl deskriptor epoll instanci */
		check_error(epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &currEvent) != -1, "....");
	}
	
	/* niz struktura u koje ce epoll upisati one na kojima se nesto desilo */
	struct epoll_event activeFds[10];
	/* flag koji signalizira da li je max inicijalizovan */
	int initialized = 0;
	/* trenutni max */
	int max = 0;
	/* ime fajla u kome je pronadjen trenutani max */
	char* maxName;
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
					
					/* ako je max inicijalizovan */
					if (initialized) {
						
						/* azuriramo po potrebi */
						if (x > max) {
							max = x;
							maxName = data->name;
						}
					}
					else {
						/* ako nije inicijalizujemo */
						max = x;
						maxName = data->name;
						
						initialized = 1;
					}
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
				/* oslobadjamo memoriju */
				free(data);
				/* umanjujemo brojac otvorenih fajlova */
				nfd--;
			}
		}
	}
	
	/* stampamo ime fajla i max */
	char* name = strrchr(maxName, '/');
	printf("%d %s\n", max, name != NULL ? name : maxName);
	
	/* zatvaramo epoll instancu */
	close(epollFd);
	
	exit(EXIT_SUCCESS);
}
