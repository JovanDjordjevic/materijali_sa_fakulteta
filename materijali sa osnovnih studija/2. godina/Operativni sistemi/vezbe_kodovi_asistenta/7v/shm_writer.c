/* Program ilustruje komunikaciju procesa pomocu deljene memorije
 *
 * Writer -> kreira i mapira blok memorije i upisuje neki sadrzaj
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

void* createShmBlock(char* path, unsigned size);

int main(int argc, char** argv){
	
	check_error(argc == 2, "...");
	
	/* kreiramo i mapiramo memorijski blok u koji cemo upisati 10 intova */
	int memSize = sizeof(int)*10;
	int* array = createShmBlock(argv[1], memSize);
	
	/* upisujemo sadrzaj u mapirani region */
	int i;
	for (i = 0; i < 10; i++)
		array[i] = i;
	
	/* unmapiramo sadrzaj koji smo ranije mapirali */
	check_error(munmap(array, memSize) != -1, "munmap failed");
	
	exit(EXIT_SUCCESS);
}

void* createShmBlock(char* path, unsigned size) {
	/* kreiramo objekat deljene memorije */
	int memFd = shm_open(path, O_RDWR | O_CREAT, 0600);
	check_error(memFd != -1, "shm_open failed");
	
	/* postavljamo velicinu fajla na odgovarajucu */
	check_error(ftruncate(memFd, size) != -1, "ftruncate failed");
	
	/* mapiramo sadrzaj fajla 
	 * BITNO:
	 * flagovi sa kojima se mapira memorija moraju da odgovaraju modu u kome je otvoren fajl
	 */
	void* addr;
	check_error(MAP_FAILED != (addr = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_SHARED, memFd, 0)), "...");
	/* zatvaramo fajl deskriptor */
	close(memFd);
	
	/* vracamo pokazivac na mapirani blok */
	return addr;
}
