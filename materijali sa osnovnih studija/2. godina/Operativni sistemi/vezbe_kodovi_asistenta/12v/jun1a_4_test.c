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
	
	int fd = open(argv[1], O_RDWR);
	check_error(fd != -1, "..");
		
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
		
	fcntl(fd, F_SETLK, &lock);
		
	sleep(10);	
		
	lock.l_type = F_UNLCK;	
	fcntl(fd, F_SETLK, &lock);			
	
	exit(EXIT_SUCCESS);
}
