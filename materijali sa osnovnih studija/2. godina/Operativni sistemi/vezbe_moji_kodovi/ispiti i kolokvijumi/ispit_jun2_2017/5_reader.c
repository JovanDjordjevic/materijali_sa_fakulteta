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
   
   for(i=0;i<data->arrayLen;i++){
     
     int cnt=0;
     int x=1;
     int y=data->array[i];
       while(y!=0){
          if(y&x) cnt++;
          y=y>>1;
       }
     if(cnt>=4) printf("%d ",data->array[i]);
     
   }
   printf("\n");

    check_error(munmap(data,size)!=-1,"unmap");

  exit(EXIT_SUCCESS);
}
