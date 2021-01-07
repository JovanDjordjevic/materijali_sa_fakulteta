/* Program ilustruje obradu signala */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <signal.h>

#define check_error(expr, userMsg)\
	do {\
		if (!(expr)) {\
			perror(userMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while (0)\

int shouldTerminate = 0;	

/* signal handler za sigInt signal */
void SigIntHandler(int signum) {
	
	/* printf nije signal safe i ovo je samo ilustracije radi 
	 * U realnosti u signalima smeju da se koriste samo funkcije koje
	 * su reentrant safe.
	 */
	printf("sigint caught");
}

/* signal handler za sigTerm signal */
void SigTermHandler(int signum) {
	
	/* printf nije signal safe i ovo je samo ilustracije radi */
	printf("sigterm caught");
	shouldTerminate = 1;
}
	
int main(int argc, char** argv){
	
	/* saznajemo pid procesa da bismo mogli da mu saljemo signale iz konzole
	 * pomocu kill komande
	 */
	printf("PID: %d\n", (int)getpid());
	
	do {
		/* postavljamo handler za obradu signala
		 *
		 * U C99, handler vazi samo za jednu obradu signala. zato ga postavljamo u svakoj iteraciji petlje
		 *
		 * U ANSI C-u, jedno postavljen handler vazi trajno. Da biste to postigli na vrhu mora @define GNU_SOURCE
		 */
		check_error(signal(SIGINT, SigIntHandler) != SIG_ERR, "signal failed");
		check_error(signal(SIGTERM, SigTermHandler) != SIG_ERR, "signal failed");
		
		printf("Signal setup finished\n");
		
		/* blokiramo proces sve dok se ne desi neki signal */
		pause();
		
		printf("Signal caught\n");
		
	} while (!shouldTerminate);
	
	exit(EXIT_SUCCESS);
}
