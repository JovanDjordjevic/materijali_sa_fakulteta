/* Program ilustruje komunikaciju procesa pomocu deljene memorije
 *
 * Reader -> mapira blok memorije i cita sadrzaj
 */
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/mman.h>

#define check_error(expr, userMsg)\
	do {\
		if (!(expr)) {\
			perror(userMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while (0)\

void* GetShmBlock(char* path, unsigned* size);

int main(int argc, char** argv){
	
	check_error(argc == 2, "...");
	
	/* memorijski mapiramo postojeci fajl */
	unsigned size = 0;
	int* array = GetShmBlock(argv[1], &size);
	int n = size/sizeof(int);
	
	/* citamo sadrzaj u mapiranom regionu */
	int i;
	for (i = 0; i < n; i++)
		printf("%d ", array[i]);
	
	printf("\n");
	
	/* unmapiramo sadrzaj koji smo ranije mapirali */
	check_error(munmap(array, size) != -1, "munamp failed");
	
	exit(EXIT_SUCCESS);
}

void* GetShmBlock(char* path, unsigned* size) {
	
	/* otvaramo objekat deljene memorije */
	int memFd = shm_open(path, O_RDWR, 0600);
	check_error(memFd != -1, "shm_open failed");
	
	/* citamo velicinu fajla
	 *
	 * BITNO:
	 * ovde je jedina razlika izmedju reader-a i writer-a
	 */
	struct stat fInfo;
	check_error(fstat(memFd, &fInfo) != -1, "stat failed");
	*size = fInfo.st_size;
	
	/* mapiramo sadrzaj fajla 
	 * BITNO:
	 * flagovi sa kojima se mapira memorija moraju da odgovaraju modu u kome je otvoren fajl
	 */
	void *addr;
	check_error(MAP_FAILED != (addr = mmap(NULL, *size, PROT_READ|PROT_WRITE,MAP_SHARED,memFd,0)), "mmap failed");
	/* zatvaramo fajl deskriptor */
	close(memFd);
	
	/* vracamo pokazivac na mapirani blok */
	return addr;
}
