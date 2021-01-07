#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>

#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<sys/mman.h>
#include<semaphore.h>
#include<string.h>

#define check_error(expr,userMsg)\
         do{\
           if(!(expr)){\
            fprintf(stderr,"%s\n",userMsg);\
            exit(EXIT_FAILURE);\
            }\
           }while(0);

#define MAX_SIZE  1024           

typedef struct{
  char message[MAX_SIZE];
  sem_t sem_write;
  sem_t sem_read;
}shmData_t;

void* createShmBlock(const char *path, unsigned size){

  int memFd=shm_open(path, O_RDWR | O_CREAT,0600);
   check_error(memFd!=-1,"shm open fail");
   
  check_error(ftruncate(memFd,size)!=-1,"ftruncate failed");
   
  void *addr;
  addr=mmap(NULL,size,PROT_READ | PROT_WRITE,MAP_SHARED,memFd,0);
   check_error(addr!=MAP_FAILED,"mmap failed");
   
  close(memFd);
  return addr;
}

int main(int argc,char **argv){
  
  check_error(argc==2,"argumenti");
  
  unsigned size=sizeof(shmData_t);
  shmData_t *data=createShmBlock(argv[1],size);
  
  check_error(sem_init(&(data->sem_write),1,1)!=-1,"sem W init fail"); //na pocetku moze da se pise
  check_error(sem_init(&(data->sem_read),1,0)!=-1,"sem R init fail"); //na pocetku NE MOZE da se cita
  
  char buffer[MAX_SIZE];
  
  do{
  
     scanf("%s",buffer);     
        check_error(sem_wait(&(data->sem_write))!=-1,"sem wait fail");  //zakljuvcavamo pisanje za ostale
     strcpy(data->message,buffer);  //mi pisemo sta treba
        check_error(sem_post(&(data->sem_read))!=-1,"sem post failed"); //otkljucavamo citanje za ostale
  }while(strcmp(buffer,"quit"));
  
  check_error(munmap(data,size)!=-1,"munmap failed");
  check_error(shm_unlink(argv[1])!=-1,"shm unlink fail");
  
  exit(EXIT_SUCCESS);
}





















