/* Napisati program koji kao argumente komandne linije prima putanje do 
 * FIFO fajlova. Program istovremeno za sve fajlove ceka na dogadjaj da 
 * je kroz neki FIFO stigao podatak koriscenjem poll interfejsa. Kroz 
 * FIFO fajlove pristizu samo celi brojevi, cita se sve dok se ne zatvore 
 * svi FIFO fajlovi na strani koja pise u FIFO. Na standardni izlaz ispisati 
 * maksimalni procitan broj i naziv FIFO fajla (ne putanju nego NAZIV).
 */ 
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <poll.h>

#define check_error(expr, userMsg)\
	do { \
		if (!(expr)) {\
			perror(userMsg);\
			exit(EXIT_FAILURE); \
		}\
	} while (0)
	

int main(int argc, char** argv) {
	
	check_error(argc > 1, "....");
	
	/* kreiramo niz struktura pollfd */
	int nfd = argc - 1;
	struct pollfd* fds = malloc(sizeof(struct pollfd)*nfd);
	check_error(fds != NULL, "...");
	
	/* niz fajl strimova koje pridruzujemo fajl deskriptorima */
	FILE** fstreams = malloc(sizeof(FILE*)*nfd);
	check_error(fstreams != NULL, "...");
	
	/* inicijalizujemo pollfd strukture */
	for (int i = 0; i < nfd; i++) {
		
		/* otvaramo fajl deskriptore - obavezno O_NONBLOCK */
		fds[i].fd = open(argv[i+1], O_RDONLY | O_NONBLOCK);
		check_error(fds[i].fd != -1, "....");
		
		/* otvaramo fajl strim nad fajl deskriptorom */
		fstreams[i] = fdopen(fds[i].fd, "r");
		check_error(fstreams[i] != NULL, "...");
		
		/* inicijalizujemo aktivnosti koje hocemo da nadgledamo */
		fds[i].events = POLLIN | POLLERR | POLLHUP;
		/* resetujemo registrovane dogadjaje
		 * BITNO:
		 * ovaj korak ne sme da se preskoci
		 */
		fds[i].revents = 0;
	}
	
	/* flag koji govori da li smo inicijalizovali max ili ne */
	int initilized = 0;
	/* trenutni max */
	int max = 0;
	/* fajl u kome je taj trenutni max */
	char* maxName = NULL;
	/* brojac otvorenih fajlova */
	int nfd1 = nfd;
	/* u petlji */
	while (nfd1) {
		
		/* cekamo na dogadjaj */
		int retVal = poll(fds, nfd, -1);
		check_error(retVal != -1, "...");
		
		/* u petlji, prolazimo kroz sve fajl deskriptore */
		for (int i = 0; i<nfd; i++) {
			
			/* ako je fajl desktiptor spreman za citanje */
			if (fds[i].revents & POLLIN) {
				/* citamo brojeve sve do kraja */
				int x;
				while (fscanf(fstreams[i], "%d", &x) == 1) {
					
					/* ako je max vec inicijalizovan */
					if (initilized) {
						/* azuriramo po potrebi */
						if (x > max) {
							
							max = x;
							maxName = argv[i+1];
						}
					}
					else {
						/* ako nije, inicijalizujemo ga */
						max = x;
						maxName = argv[i+1];
						initilized = 1;
					}
				}
				/* provera gresaka */
				check_error(feof(fstreams[i]), "...");
				
				/* brisemo registrovani dogadjaj 
				 * BITNO:
				 * ne sme da se preskoci
				 */
				fds[i].revents = 0;
			}
			/* ako se desila greska na fajl deskriptoru ili ako je druga
			 * strana zatvorila svoj kraj
			 */
			else if (fds[i].revents & (POLLERR | POLLHUP)) {
				
				/* zatvaramo strim */
				fclose(fstreams[i]);
				/* fd postavljamo na -1 */
				fds[i].fd = -1;
				/* resetujemo polje koje definise nadgledane dogadjaje */
				fds[i].events = 0;
				/* resetujemo registrovani dogadjaj */
				fds[i].revents = 0;
				/* umanjujemo brojac otvorenih fajlova */
				nfd1--;
			}
		}
	}
	
	/* pronalazimo ime fajla */
	char* fName = strrchr(maxName, '/');
	printf("%d %s\n", max, fName != NULL ? fName : maxName);
	
	/* oslobadjamo resurse */
	free(fds);
	free(fstreams);
	
	exit(EXIT_SUCCESS);
}
