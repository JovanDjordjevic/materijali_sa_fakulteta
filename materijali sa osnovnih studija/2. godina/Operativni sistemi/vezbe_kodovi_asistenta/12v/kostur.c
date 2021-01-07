#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <poll.h>

#define check_error(expr, userMsg)\
	do { \
		if (!(exprs)) {\
			perror(userMsg);\
			exit(EXIT_FAILURE); \
		}\
	} while (0)
	

int main(int argc, char** argv) {
	
	exit(EXIT_SUCCESS);
}
