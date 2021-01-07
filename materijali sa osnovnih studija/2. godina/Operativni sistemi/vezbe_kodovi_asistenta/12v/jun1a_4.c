/* Napisati program koji kao argument komandne linije prima putanju do 
 * fajla. Fajl sadrzi tekst u kome se nalaze brojevi. Program treba da 
 * cita rec po rec i ukoliko je procitana rec broj, da se potrudi da ga 
 * zakljuca. Ukoliko je broj vec zakljucan (od strane drugog procesa), 
 * program normalno nastavlja dalje sa obradom. Ispisati na standardni 
 * izlaz broj uspesno zakljucanih brojeva (ispis je samo jedan broj).
 * 
 * Dodatno, u zadatku je uradjena izmena vrednosti koje se nalaze u fajlu.
 */ 
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>

#define check_error(expr, userMsg)\
	do { \
		if (!(expr)) {\
			perror(userMsg);\
			exit(EXIT_FAILURE); \
		}\
	} while (0)

#define MAX_SIZE (1024)	

int main(int argc, char** argv) {
	
	check_error(argc == 2, "...");
	/* otvaramo fajl */
	int fd = open(argv[1], O_RDWR);
	check_error(fd != -1, "..");
	/* pridruzujemo fajl strim fajl deskriptoru
	 * BITNO:
	 * mod u kome otvarate fajl mora da bude isti kao mod sa kojim otvarate
	 * fajl strim i mora da odgovara onome sto planirate da radite sa fajlom, 
	 * tj. otvaranje fajla u RD modu i zakljucavanje sa F_WRLCK nije dozvoljeno.
	 */ 
	FILE* f = fdopen(fd, "r+");
	check_error(f != NULL, "....");
	
	/* bafer u koji smestamo reci koje citamo */
	char buffer[MAX_SIZE];
	int numLocked = 0;
	/* dok god je citanje uspesno */
	while (fscanf(f, "%s", buffer) == 1) {
		
		/* pousavamo da prebacimo rec u broj */
		char* error = NULL;		
		int num = strtol(buffer, &error, 10);
		/* ako se desila greska, tj. ako procitana rec nije broj */
		if (buffer[0] != '\0' && *error != '\0') {
			/* prelazimo na sledecu rec */
			continue;
		}
		
		/* definisemo strukturu koja opisuje zakljucavanje */		
		struct flock lock;
		lock.l_type = F_WRLCK;			/* katanac za pisanje , jer samo sa njim
										 * mozemo da saznamo da li neko drugi
										 * drzi neki drugi katanac na istom regionu
										 * Katanac za citanje nam to ne omogucava
										 * u slucaju da neko drugi ima katanac za pisanje
										 * na istom regionu.
										 */
		lock.l_whence = SEEK_CUR;		/* trenutni polozaj */
		/* BITNO:
		 * s obzirom da koristimo strimove, nas trenutni polozaj se dobija 
		 * sa ftell(...), nikako sa lseek(...)
		 */ 
		lock.l_start = ftell(f);
		/* zakljucavamo unazad */
		lock.l_len = -strlen(buffer);
		
		/* pokusamo da zakljucamo region */
		int retVal = fcntl(fd, F_SETLK, &lock);
		
		/* ako zakljuavanje nije uspelo */
		if (retVal == -1) {
			/* ako je razlog pucanje nije blokiranje od strane drugog procesa */
			if (errno != EACCES && errno != EAGAIN) {
				/* prekidamo program */
				check_error(0, "...");
			}
		}
		else {
			
			/* uvecavamo brojac uspesno zakljucanih brojeva */
			numLocked++;
			/* uvecavamo broj */
			num += 2;
			
			/* vracamo fajl offset u nazad */
			fseek(f, -strlen(buffer), SEEK_CUR);
			/* prepisujemo broj novim brojem */
			fprintf(f, "%d", num);
			
			/* otkljucavamo zakljucani region */
			lock.l_type = F_UNLCK;			
			check_error(fcntl(fd, F_SETLK, &lock) != -1, "...");
		}
	}
	 
	/* proveravamo greske */
	check_error(feof(f), "...");
	
	/* stampamo broj uspesno zakljucanih */
	printf("%d\n", numLocked);
	
	/* zatvaramo fajl */
	fclose(f);
	
	exit(EXIT_SUCCESS);
}
