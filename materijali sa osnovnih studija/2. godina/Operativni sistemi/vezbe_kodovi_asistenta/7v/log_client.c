/* Program ilustruje sinhronizaciju pristupa deljenoj memoriji
 * Klijent mapira postojeci blok deljene memorije i cita/pise po njemu.
 */
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <string.h>

#define check_error(expr, userMsg)\
	do {\
		if (!(expr)) {\
			perror(userMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while (0)
	
#define MAX_SIZE (1024)

/* struktura kojom se opisujuje blok deljene memorije
 *
 * BITNO:
 * u svim procesima koji mapiraju isti blok deljene memorije, struktura mora da bude
 * definisana identicno. Svaka razlika u definiciji povlaci haos u programu i vrlo verovatno deadlock
 */
typedef struct {
	sem_t writeLock;
	sem_t readLock;
	char buffer[MAX_SIZE];
} shmData;

void* GetShmBlock(char* path, unsigned* size);

int main(int argc, char** argv){
	
	check_error(argc == 2, "..");
	
	/* citamo i mapiramo blok deljene memorije */
	unsigned size = 0;
	shmData* data = GetShmBlock(argv[1], &size);
	
	char buffer[MAX_SIZE];
	
	/* u petlji */
	do{
		/* pomocu semafora sinhronizujemo pristup deljenoj memoriji
		 *
		 * BITNO:
		 * svaki pristup semaforu je izmena sadrzaja deljene memorije, pa mapiranje
		 * MORA da ukljucuje i flag za pisanje. Isto vazi i za otvaranje fajla deljene memorije
		 */
		check_error(sem_wait(&(data->readLock)) != -1, "...");
		/* citamo poruku iz bloka deljene memorije */
		strcpy(buffer, data->buffer);
		/* obavestavamo drugi proces da moze da upise novu poruku u memoriju */
		check_error(sem_post(&(data->writeLock)) != -1, "...");
		/* prikazujemo primeljenu poruku */
		printf("%s\n", buffer);
		
		/* sve dok se ne ispuni signal kraja */
	} while (strcmp(buffer, "quit"));
	
	/* unmapiramo deljenu memoriju */
	check_error(munmap(data, size) != -1, "...");
		
	exit(EXIT_SUCCESS);
}

void* GetShmBlock(char* path, unsigned* size) {
	
	/* otvaramo fajl deljene memorije -> Obratiti paznju na flagove */
	int memFd = shm_open(path, O_RDWR, 0600);
	check_error(memFd != -1, "shm_open failed");
	
	/* citamo velicinu fajla, da bismo znali koliko treba da mapiramo */
	struct stat fInfo;
	check_error(fstat(memFd, &fInfo) != -1, "stat failed");
	*size = fInfo.st_size;
	
	/* mapiramo fajl -> Obratiti paznju na flagove */
	void *addr;
	check_error(MAP_FAILED != (addr = mmap(NULL, *size, PROT_READ|PROT_WRITE,MAP_SHARED,memFd,0)), "mmap failed");
	/* zatvaramo fajl deskriptor */
	close(memFd);
	
	/* vracamo adresu mapiranog regiona */
	return addr;
}
