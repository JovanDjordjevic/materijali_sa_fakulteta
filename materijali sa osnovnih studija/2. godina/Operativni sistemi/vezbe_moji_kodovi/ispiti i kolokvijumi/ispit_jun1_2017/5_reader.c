//kod mene racuna kako treba ali na grejderu 20%
#define _XOPEN_SOURCE 700
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
#include<math.h>

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
float array[ARRAY_MAX];
unsigned arrayLen;
}OsInputData;

void *getBlock(const char *path,int *size){
   
   int memFd=shm_open(path,O_RDWR,0600);
     check_error(memFd!=-1,"shm open");
   struct stat fInfo;  
    check_error(fstat(memFd,&fInfo)!=-1,"stat");
  *size=fInfo.st_size;
  
  void *addr;
  addr=mmap(NULL,*size,PROT_READ | PROT_WRITE,MAP_SHARED,memFd,0);
  check_error(addr!=MAP_FAILED,"mmap");
  
   close(memFd);
   return addr;
}
                  
int main(int argc, char **argv){
    
    check_error(argc==2,"args");
    
    int size; 
    OsInputData *data=getBlock(argv[1],&size);
   
   int i; 
   check_error(sem_wait(&(data->inDataReady))!=-1,"wait");
   
   double ni=0;
   unsigned N=data->arrayLen;
   for(i=0;i<N;i++){
     ni+=data->array[i];     
   }
   ni=ni/(double)N;
   
   double o=0;
   for(i=0;i<N;i++){
     o+=(data->array[i]-ni)*(data->array[i]-ni);
   }
   o=o/(double)N;
   o=sqrt(o);
   
   printf("%lf\n",o);
   
   check_error(sem_post(&(data->inDataReady))!=-1,"post");   
    
    
    check_error(munmap(data,size)!=-1,"unmap");

  exit(EXIT_SUCCESS);
}
