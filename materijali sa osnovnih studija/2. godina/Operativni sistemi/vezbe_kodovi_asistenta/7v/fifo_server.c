/* program ilustruje komunikaciju dva procesa koji nisu u relaciju
 * roditelj-dete pomocu imenovanih pajpova 
 *
 * Server - salje poruke sve dok korisnik ne unese signal za kraj
 */
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

#define MAX_SIZE (256)

#define check_error(expr, userMsg)\
	do {\
		if (!(expr)) {\
			perror(userMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while (0)\
	
int main(int argc, char** argv){
	
	check_error(argc == 2, "...");
	
	/* server kreira imenovani fifo pomocu koga ce se odvijati komunikacija */
	check_error(mkfifo(argv[1], 0644) !=-1, "mkfifo failed");
	
	/* server otvara fifo u modu za pisanje, jer ce slati poruke
	 * BITNO:
	 * klijent mora da otvori fifo u suprotnom modu, tj. u modu za citanje
	 *
	 * BITNO 2:
	 * fifo se nikada ne otvara kao O_RDWR -> nedefinisano ponasanje
	 */
	int fd = open(argv[1], O_WRONLY);
	check_error(fd != -1, "open failed");
	
	/* inicijalizujemo sito za generisanje slucajnih brojeva */
	srand(time(NULL));
	char buf[MAX_SIZE];
	/* u petlji */
	do {
		/* generisemo broj koji treba poslati i upisujemo ga u bafer */
		sprintf(buf, "%d\n", rand());
		printf("Sending: %s\n", buf);
		
		/* saljemo broj iz bafera */
		check_error(write(fd, buf, strlen(buf)) != -1, "write failed");
		
		/* pitamo korisnika da li treba da nastavimo */
		printf("Continue: (yes/no) ");
		scanf("%s", buf);
		/* proveravamo signal za kraj */
	} while (strcasecmp(buf, "no"));
	
	/* zatvaramo fajl */
	close(fd);
	
	exit(EXIT_SUCCESS);
}
