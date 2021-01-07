/* program kreira child proces i ilustruje razlikovanje grana
 * child i parent procesa
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
	
	/* pozivamo fork i kreiramo novi proces */
	pid_t pid = fork();
	/* obavezno proveravamo povratnu vrednost */
	check_error(pid != -1, "fork failed");
	
	/* povratno vrednost fork-a nam govori u kojoj grani se nalazimo
	 * povratna vrednost veca od nule znaci da se nalazimo u parent grani
	 * i taj broj je bas pid novog procesa koji samo kreirali
	 */
	if (pid > 0) { // parent
		
		/* sopstveni pid, tj. process ID dobijamo pozivom getpid() */
		printf("Ovo ispisuje samo parent\n");
		printf("Parent: pid = %jd, child id = %jd\n", (intmax_t)getpid(), (intmax_t)pid);
	}
	else { //child
		/* ako je povratna vrednost fork-a nula, onda se nalazimo u child grani */
		
		/* sopstveni pid dobijamo getpid() pozivom, a pid parenta dobijamo getppid() pozivom */
		printf("Ovo ispisuje samo child\n");
		printf("Child: pid = %jd, parent id = %jd\n", (intmax_t)getpid(), (intmax_t)getppid());
		
		/* nakon sto zavrsi sa radom, child mora da pozove exit */
		exit(EXIT_SUCCESS);
	}
	
	/* parent mora da saceka da child zavrsi sa radom i pravilno obradi zombije */
	check_error(wait(NULL) != -1, "wait null");

	printf("Ovo stampaju samo parent\n");
	
	exit(EXIT_SUCCESS);
}
