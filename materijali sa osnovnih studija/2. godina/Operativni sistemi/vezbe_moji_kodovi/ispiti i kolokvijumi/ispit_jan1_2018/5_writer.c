#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

#include<errno.h>
#include<time.h>
#include<string.h>
#include<sys/wait.h>
#include<signal.h>
#include<poll.h>
#include<limits.h>
#include<semaphore.h>
#include<sys/mman.h>

#define check_error(expr,userMsg)\
                do{\
                  if(!(expr)){\
                    fprintf(stderr,"%s\n",userMsg);\
                    exit(EXIT_FAILURE);\
                   }\
                 }while(0);

#define RD_END (0)
#define WR_END (1)
#define ARRAY_MAX (1024)

typedef struct{
  sem_t inDataReady;
  sem_t dataProcessed;
  char str[ARRAY_MAX];
}OsInputData;

void *createBlock(const char *path,unsigned size){
  
  int memFd=shm_open(path,O_RDWR|O_CREAT,0600);
    check_error(memFd!=-1,"shm open");
  
  check_error(ftruncate(memFd,size)!=-1,"trunc");
  
  void *addr;
  addr=mmap(NULL,size,PROT_READ | PROT_WRITE,MAP_SHARED,memFd,0);
    check_error(addr!=MAP_FAILED,"mmap");  
  
  close(memFd);
  return addr;
}


int main(int argc, char **argv){
   
   check_error(argc==2,"args");
   
   unsigned size=sizeof(OsInputData);
   OsInputData *data=createBlock(argv[1],size);
   
   check_error(sem_init(&(data->inDataReady),1,0)!=-1,"init1");
   check_error(sem_init(&(data->dataProcessed),1,1)!=-1,"init2");
   
   check_error(sem_wait(&(data->dataProcessed))!=-1,"wait");
   
   scanf("%s",data->str);
   
   check_error(sem_post(&(data->inDataReady))!=-1,"post");
   
   check_error(munmap(data,size)!=-1,"munmap");
   
  exit(EXIT_SUCCESS);
}
                 
