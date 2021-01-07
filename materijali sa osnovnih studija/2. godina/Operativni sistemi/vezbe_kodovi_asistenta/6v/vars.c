/* program ilustruje potpuno kopiranje adresnih prostora prilikom kreiranja 
 * child procesa i nezavisnost promenljivih u parent u child granama 
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <sys/wait.h>

#define check_error(expr, msg)\
	do {\
		if (!(expr)) {\
			perror(msg);\
			exit(EXIT_FAILURE); \
		} \
	} while(0)

int main(void){
	
	/* lokalne promenljive u mainu */
	int x = 10;
	int y = 50;
	
	/* ova linija se stampa samo jednom, jer pripada samo parentu.
	 * u ovom momentu jos uvek nije kreirano dete proces 
	 */
	printf("Before fork: x(%d), y(%d)\n", x, y);
	
	/* kreiranje deteta 
	 * kompletan kod koji je napisan ispod ove linije je zajednicki i za parenta
	 * i za childa
	 *
	 * Sve promenljive koje su definisane pre ove linije se kopiraju u potpunosti i u 
	 * adresni prostor parenta i u adresni prostor deteta. 
	 */
	pid_t pid = fork();
	/* obavezna provera povratnih vrednosti */
	check_error(pid != -1, "fork failed");
	
	/* jedini nacin da razlikujemo da li smo u parent ili child procesu je pomocu povratne vrednosti
	 * fork-a
	 *
	 * vrednost veca od nule -> parent grana
	 * vrednost jednaka nuli -> child grana
	 */
	if (pid > 0) { // parent
		
		/* kopija promenljivih koja pripada parentu
		 *
		 * BITNO:
		 * promena vrednosti u parentu nema nikakvog uticaja na vrednost promenljivih u child-u, jer
		 * i jedan i drugi proces imaju svoje kopije tih promenljivih 
		 */
		x += 5;
		y -= 5;
		
		/* parent stampa svoje vrednosti */
		printf("Parent: x(%d), y(%d)\n", x, y);
	}
	else { // child
	
		/* child proces vrsi svoju izmenu podataka */
		x -= 5;
		y += 5;
		
		/* i prikazuje ih */
		printf("Child: x(%d), y(%d)\n", x, y);
		
		/* nakon izmene, child se zavrsava */
		exit(EXIT_SUCCESS);
	}
	
	/* parent je duzan da saceka da se child proces zavrsi i pravilno obradi
	 * PCB child-a i na taj nacin izbegne sejanje zombija i bespotrebno trosenje
	 * resursa sistema. 
	 */
	check_error(wait(NULL) != -1, "wait failed");
	
	printf("After wait: x(%d), y(%d)\n", x, y);
	
	exit(EXIT_SUCCESS);
}
