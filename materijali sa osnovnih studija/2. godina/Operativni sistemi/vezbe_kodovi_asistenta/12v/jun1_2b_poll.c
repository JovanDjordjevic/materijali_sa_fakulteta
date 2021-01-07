/* Napisati program koji kao argumente komandne linije prima putanje do 
 * FIFO fajlova. Program istovremeno za sve fajlove ceka na dogadjaj da 
 * je kroz neki FIFO stigao podatak koriscenjem poll interfejsa. Kroz 
 * FIFO fajlove pristizu samo celi brojevi, cita se sve dok se ne zatvore 
 * svi FIFO fajlovi na strani koja pise u FIFO. Na standardni izlaz ispisati 
 * maksimalnu sumu brojeva koji se nalaze u jednom FIFO fajlu i naziv tog 
 * FIFO fajla (ne putanju nego NAZIV).
 */ 
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <poll.h>
#include <string.h>

#define check_error(expr, userMsg)\
	do {\
		if (!(expr)) {\
			perror(userMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while (0)
	

int main(int argc, char** argv) {
	
	check_error(argc > 1, "...");
	
	/* inicijalizujemo niz lokalnih suma */
	int nfd = argc-1;
	int* localSum = malloc(sizeof(int)*(argc - 1));
	check_error(localSum != NULL, "...");
	
	for (int i = 0; i < nfd; i++) {
		localSum[i] = 0;
	}
	
	/* kreiramo niz struktura pollfd */
	struct pollfd* fds = malloc(sizeof(struct pollfd)*nfd);
	check_error(fds != NULL, "...");
	
	/* niz fajl strimova koje pridruzujemo fajl deskriptorima */
	FILE** fStreams = malloc(nfd*sizeof(FILE*));
	check_error(fStreams != NULL, "...");
	
	/* inicijalizujemo pollfd strukture */
	for (int i = 0; i < nfd; i++) {
		
		/* otvaramo fajl deskriptore - obavezno O_NONBLOCK */
		fds[i].fd = open(argv[i+1], O_RDONLY | O_NONBLOCK);
		check_error(fds[i].fd != -1, "...");
		
		/* otvaramo fajl strim nad fajl deskriptorom */
		fStreams[i] = fdopen(fds[i].fd, "r");
		check_error(fStreams[i] != NULL, "...");
		
		/* inicijalizujemo aktivnosti koje hocemo da nadgledamo */
		fds[i].events = POLLIN | POLLERR | POLLHUP;
		/* resetujemo registrovane dogadjaje
		 * BITNO:
		 * ovaj korak ne sme da se preskoci
		 */
		fds[i].revents = 0;
	}
	
	/* brojac otvorenih fajlova */
	int nfd1 = nfd;
	
	/* u petlji */
	while (nfd1) {
		
		/* cekamo na dogadjaj */
		int retVal = poll(fds, nfd, -1);
		check_error(retVal != -1, "...");
		
		/* u petlji, prolazimo kroz sve fajl deskriptore */
		for (int i = 0; i < nfd; i++) {
			
			/* ako je fajl desktiptor spreman za citanje */
			if (fds[i].revents & POLLIN) {
				/* sabiramo sve brojeve do kraja ulaza */
				int x;
				while (fscanf(fStreams[i], "%d", &x) == 1) {
					localSum[i] += x;
				}
				/* proveravamo greske */
				check_error(feof(fStreams[i]), "...");
				
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
				fclose(fStreams[i]);
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
	
	/* pronalazimo fajl sa najvecom sumom brojeva */
	int max = localSum[0];
	int maxInd = 0;
	for (int i = 1; i < nfd; i++) {
		if (localSum[i] > max) {
			max=localSum[i];
			maxInd = i;
		}
	}
	
	/* stampamo najvecu sumu i naziv fajla */
	char* fName = strrchr(argv[maxInd+1], '/');
	printf("%d %s\n", max, fName != NULL ? fName : argv[maxInd+1]);
	
	/* oslobadjamo resurse */
	free(fds);
	free(fStreams);
	free(localSum);
	
	exit(EXIT_SUCCESS);
}
			
