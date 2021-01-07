/* program ilustruje upotrebu exevp */
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
	
void createProcess(char** p);


int main(int argc, char** argv) {
	
	/* kroz argumente komandne linije se salje komanda koju treba da pokrenemo */
	check_error(argc > 1, "...");
	
	/* pakujemo argumente kao niz stringova koje ocekuje execvp */
	char** program = NULL;
	program = malloc(sizeof(char*)*(argc + 1));
	check_error(program != NULL, "malloc failed");
	
	program[0] = malloc(strlen(argv[1]) + 1);
	check_error(program[0] != NULL, "...");
	strcpy(program[0], argv[1]);
	
	char* ptr = strrchr(argv[1], '/');
	ptr = ptr != NULL ? ptr+1 : argv[1];
	program[1] = malloc(strlen(ptr) + 1);
	check_error(program[1] != NULL, "...");
	strcpy(program[1], ptr+1);
	
	for (int i = 2; i < argc; i++) {
		
		program[i] = malloc(strlen(argv[i]) + 1);
		check_error(program[i] != NULL, "...");
		strcpy(program[i], argv[i]);
	}
	
	program[argc] = NULL;
	
	/* izvrsavamo komandu u dete procesu */
	createProcess(program);
	
	/* hvatamo status zavrsetka deteta i obradjujemo zombije */
	int status = 0;
	check_error(wait(&status) != -1, "...");
	
	/* pisemo korisniku poruku da li je program uspesno zavrsen ili ne */
	if (WIFEXITED(status) && (WEXITSTATUS(status) == EXIT_SUCCESS)) {
		
		printf("Sve ok\n");
	}
	else {
		printf("Greska\n");
	}
	
	/* oslobadjamo resurse */
	for (int i = 0; i < argc + 1; i++)
		free(program[i]);

	free(program);
	
	exit(EXIT_SUCCESS);
}

void createProcess(char** p) {
	
	/* kreiramo dete proces */
	pid_t pid = fork();
	
	check_error(pid != -1, "...");
	
	/* i child grani */
	if (pid == 0) {
		
		/* pomocu execvp izvrsavamo komandu */
		check_error(execvp(p[0], p+1) != -1, "exec failed");
	}
	
}
