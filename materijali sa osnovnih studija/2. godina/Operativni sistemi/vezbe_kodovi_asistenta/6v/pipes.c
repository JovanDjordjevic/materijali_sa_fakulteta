/* program ilustruje dvosmernu komunikaciju izmedju procesa */
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define check_error(expr, msg)\
	do {\
		if (!(expr)) {\
			perror(msg); \
			exit(EXIT_FAILURE);\
		}\
	}while(0)

#define RD_END (0)
#define WR_END (1)
#define MAX_SIZE (256)

int main(void) {
	
	/* komunikacija izmedju procesa koji su povezani parent-child relacijom
	 * moze da se ostvari pomocu neimenovanih pajpova.
	 *
	 * BITNO:
	 * pajp je iskljucivo jednosmetna komunikacija. Dakle, ili od parenta ka childu ili od childa ka parentu.
	 *
	 * BITNO 2:
	 * za dvosmernu komunikaciju, neophodna su dva pajpa
	 */
	
	int par2cld[2];
	int cld2par[2];
	/* kreiramo dva pajpa 
	 * BITNO:
	 * krairanje pajpova mora da se uradi pre fork poziva, da bi i parent i child
	 * imali kopije istih fajl deskriptora, tj. istih pajpova.
	 */
	check_error(pipe(par2cld) != -1, "pipe failed");
	check_error(pipe(cld2par) != -1, "pipe failed");
	
	/* kreiramo dete proces */
	pid_t pid = fork();
	check_error(pid != -1, "fork failed");
	
	
	if (pid > 0) { // parent
		
		/* u parentu zatvaramo one strane pajpova koje necemo koristiti */
		close(par2cld[RD_END]);
		close(cld2par[WR_END]);
		
		/* ucitavamo liniju sa std ulaza */
		char* line = NULL;
		size_t lineLen = 0;
		check_error(getline(&line, &lineLen, stdin) != -1, "getline failed");
		check_error(lineLen < 256, "line too long");
		
		/* i tu liniju saljemo child-u pomocu pajpa.
		 * BTINO:
		 * saljemo samo onoliko bajtova koliko ima linija, ne celokupan sadrzaj bafera
		 */
		check_error(write(par2cld[WR_END], line, lineLen) != -1, "write failed");
		
		/* citamo odgovor childa pomocu drugog pajpa */
		char buf[MAX_SIZE];
		int readBytes = 0;
		check_error((readBytes = read(cld2par[RD_END], buf,MAX_SIZE)) != -1, "read failed");
		
		/* i prikazujemo ga na ekranu */
		check_error(write(STDOUT_FILENO, buf, readBytes) != -1, "read failed");
		
		/* oslobadjamo alociranu memoriju i zatvaramo strane pajpova koje nam vise nisu potrebne */
		free(line);
		close(par2cld[WR_END]);
		close(cld2par[RD_END]);
	}
	else { // child
		
		/* child zatvara strane pajpa koje ne koristi */
		close(par2cld[WR_END]);
		close(cld2par[RD_END]);
		
		/* ceka poruku od parenta */
		char buf[MAX_SIZE];
		int bytesRead = 0;
		memset(buf, 0, MAX_SIZE);
		strcpy(buf, "Child: ");
		write(STDOUT_FILENO, buf, strlen(buf));
		
		bytesRead = read(par2cld[RD_END], buf, MAX_SIZE);
		check_error(bytesRead != -1, "read failed");
		
		/* prikazuje je na standardnom izlazu 
		 * BITNO:
		 * s obzirom da ne radimo sa streamovima, vec sa sirovim bajtovima,
		 * nije neophodno da vodimo o terminirajucoj nuli, iako je to prljava praksa
		 *
		 * U slucaju da radimo bilo sta sa stringovima, tj. sa formatiranim izlazom, morali bismo
		 * rucno da terminisemo string.
		 */
		//printf("Child:");
		check_error(write(STDOUT_FILENO, buf, bytesRead) != -1, "write failed");
		
		/* saljemo odgovor parentu pomocu drugog pajpa */
		char* s = "SUCCESS\n";
		check_error(write(cld2par[WR_END], s, strlen(s)) != -1, "write failed");
		
		/* zatvaramo strane pajpa koje nam vise ne trebaju */
		close(par2cld[RD_END]);
		close(cld2par[WR_END]);
		
		/* i prekidamo program */
		exit(EXIT_SUCCESS);
	}
	
	/* parent mora da saceka da child zavrsi sa radom i pravilno obradi zombije */
	check_error(wait(NULL)!=-1, "wait failed");
	
	exit(EXIT_SUCCESS);
}
