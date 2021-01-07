/* program ilustruje komunikaciju dva procesa koji nisu u relaciju
 * roditelj-dete pomocu imenovanih pajpova 
 *
 * Klijent - cita poruke sve dok server ne zatvori svoju stranu pajpa
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

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
	
	/* proces otvara pajp koji mu se prosledjuje kao argument komandne linije */
	int fd = open(argv[1], O_RDONLY);
	check_error(fd != -1, "open failed");
	
	/* program cita redom brojeve sve dok se ne zatvori pajp na drugoj strani
	 * tj. sve dok ne procita EOF
     */
	do {
		char buffer[MAX_SIZE];
		int bytesRead = 0;
		/* citamo sadrzaj fifo-a */
		bytesRead = read(fd, buffer, MAX_SIZE);
		/* provera gresaka */
		check_error(bytesRead != -1, "read failed");
		/* ako je EOF, prekidamo petlju */
		if (bytesRead == 0)
			break;
		/* u suprotnom. OBAVEZNO terminisemo procitani sadrzaj */
		buffer[bytesRead] = 0;
		/* prikazujemo procitani broj */
		printf("Received: %d\n", atoi(buffer));
	} while (1);
	
	/* zatvaramo fifo */
	close(fd);
	
	exit(EXIT_SUCCESS);
}
