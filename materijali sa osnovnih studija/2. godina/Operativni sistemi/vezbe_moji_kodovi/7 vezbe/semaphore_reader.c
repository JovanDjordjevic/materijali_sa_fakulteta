#include<stdio.h>
#include<stdlib.h>

#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<sys/mman.h>
#include<string.h>
#include<semaphore.h>

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

void *getShmBlock(const char *path, unsigned *size){
  
  int memFd=shm_open(path, O_RDWR,0600);
    check_error(memFd!=-1,"shm open failed");
    
  struct stat fInfo;
    check_error(fstat(memFd,&fInfo)!=-1,"stat fail");
  *size=fInfo.st_size;
  
  void *addr;
  addr=mmap(NULL,*size,PROT_READ | PROT_WRITE,MAP_SHARED,memFd,0);
   check_error(addr!=MAP_FAILED,"mmap failed");
 
 close(memFd);
 return addr;
}

int main(int argc,char **argv){
  
  check_error(argc==2,"argumenti");
  
  unsigned size;
  shmData_t *data=getShmBlock(argv[1],&size);
  
  char buffer[MAX_SIZE];
  
  do{
  
      check_error(sem_wait(&(data->sem_read))!=-1,"sem R wait failed"); //zakljucavamo citanje za ostale
    strcpy(buffer,data->message); //mi citamo sta treba
      check_error(sem_post(&(data->sem_write))!=-1,"sem E post fail"); //otkljucavamo pisanje za ostale
    printf("%s\n",buffer);  
    
  }while(strcmp(buffer,"quit"));
  
  check_error(munmap(data,size)!=-1,"munmap fail");
  
  exit(EXIT_SUCCESS);
}










