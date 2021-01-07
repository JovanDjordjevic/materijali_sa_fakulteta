#define _XOPEN_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#include<errno.h>
#include<pthread.h>
#include<string.h>
#include<sys/wait.h>
#include<signal.h>
#include<ctype.h>
#include<semaphore.h>
#include<sys/mman.h>

#define check_error(expr,userMsg)\
                do{\
                  if(!(expr)){\
                     fprintf(stderr,"%s\n",userMsg);\
                     exit(EXIT_FAILURE);\
                    }\
                  }while(0);
                  
#define check_thread(err,userMsg)\
                do{\
                  int _err=err;\
                  if(_err){\
                    errno=_err;\
                    check_error(0,userMsg);\
                   }\
                  }while(0);
#define RD_END (0)
#define WR_END (1)
#define ARRAY_MAX (1024)

typedef struct {
sem_t inDataReady;
int array[ARRAY_MAX];
unsigned arrayLen;
}OsInputData;

void *createBlock(const char *path,int size){
   
   int memFd=shm_open(path,O_RDWR | O_CREAT,0600);
     check_error(memFd!=-1,"shm open");
  check_error(ftruncate(memFd,size)!=-1,"trucn");
  
  void *addr;
  addr=mmap(NULL,size,PROT_READ | PROT_WRITE,MAP_SHARED,memFd,0);
  check_error(addr!=MAP_FAILED,"mmap");
  
   close(memFd);
   return addr;
}
                  
int main(int argc, char **argv){
    
    check_error(argc==2,"args");
    
    int size=sizeof(OsInputData);    
    OsInputData *data=createBlock(argv[1],size);
    
    check_error(sem_init(&(data->inDataReady),1,1)!=-1,"sem init"); 
    
    scanf("%u",&data->arrayLen);
    
    
    
    int i;
    for(i=0;i<data->arrayLen;i++){
      scanf("%d",&(data->array[i]));
    }
    
    
    check_error(munmap(data,size)!=-1,"unmap"); 
  exit(EXIT_SUCCESS);
}
