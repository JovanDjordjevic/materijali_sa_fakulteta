/* PRogram ilustruje sinhronizaciju pristupa deljenoj memoriji
 * Server kreira blok deljene memorije i inicijalizuje semafore
 */
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <semaphore.h>
#include <sys/mman.h>
#include <string.h>

#define check_error(expr, userMsg)\
	do {\
		if (!(expr)) {\
			perror(userMsg);\
			exit(EXIT_FAILURE);\
		}\
	} while (0)

#define MAX_SIZE (1024)

#define LOCAL_SEM (0)
#define PROC_SEM  (!LOCAL_SEM)

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


void* createShmBlock(char* path, unsigned size);
	
int main(int argc, char** argv){
	
	check_error(argc == 2, "...");
	
	/* kreiramo blok deljene memorije 
	 *
	 * BITNO:
	 * samo jedan proces kreira blok, ostali ga samo koriste
	 */
	shmData* data = (shmData*)createShmBlock(argv[1], sizeof(shmData));
	
	/* inicijalizujemo semafore 
	 *
	 * BITNO:
	 * samo jedan proces inicijalizuje semafore. Ovo su neimenovani semafori. Postoje
	 * i imenovani, za detalje TLPI.
	 */
	check_error(-1!=sem_init(&(data->writeLock),PROC_SEM,1), "...");
	check_error(-1!=sem_init(&(data->readLock),PROC_SEM,0), "...");
	
	char buffer[MAX_SIZE];
	/* u petlji */
	do {
		/* ucitavamo liniju */
		scanf("%s", buffer);
		/* pomocu semafora sinhronizujemo pristup deljenoj memoriji
		 *
		 * BITNO:
		 * svaki pristup semaforu je izmena sadrzaja deljene memorije, pa mapiranje
		 * MORA da ukljucuje i flag za pisanje. Isto vazi i za otvaranje fajla deljene memorije
		 */
		check_error(sem_wait(&(data->writeLock))!=-1, "..");
		/* upisujemo liniju u blok deljene memorije */
		strcpy(data->buffer,buffer);
		/* obavestavamo drugi proces da ima nesto novo u memoriji */
		check_error(sem_post(&(data->readLock)) != -1,"..");
		/* sve dok se ne ispuni signal kraja */
	} while(strcmp(buffer, "quit"));	
	
	/* unmapiramo deljenu memoriju */
	check_error(munmap(data, sizeof(shmData))!=-1,"..");
	/* i brisemo objekat deljene memorije */
	check_error(shm_unlink(argv[1])!=-1, "...");
	
	exit(EXIT_SUCCESS);
}

void* createShmBlock(char* path, unsigned size) {
	
	/* kreiramo fajl deljene memorije -> Obratiti paznju na flagove */
	int memFd = shm_open(path, O_RDWR | O_CREAT, 0600);
	check_error(memFd != -1, "shm_open failed");
	
	/* postavljamo mu velicinu */
	check_error(ftruncate(memFd, size) != -1, "ftruncate failed");
	
	/* mapiramo fajl -> Obratiti paznju na flagove */
	void* addr;
	check_error(MAP_FAILED != (addr = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_SHARED, memFd, 0)), "...");
	/* zatvaramo fajl deskriptor */
	close(memFd);
	
	/* vracamo adresu mapiranog regiona */
	return addr;
}
