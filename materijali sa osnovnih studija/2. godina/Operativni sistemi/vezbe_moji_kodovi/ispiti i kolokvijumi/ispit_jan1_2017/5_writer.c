#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<sys/wait.h>
#include<pthread.h>
#include<errno.h>
#include<string.h>
#include<semaphore.h>
#include<sys/mman.h>
#include<ctype.h>

#define check_error(expr,userMsg)\
             do{\
               if(!(expr)){\
                 fprintf(stderr,"%s\n",userMsg);\
                 exit(EXIT_FAILURE);\
                }\
              }while(0);

            
#define ARRAY_MAX 1024

typedef struct{
  sem_t inDataReady;
  float array[ARRAY_MAX];
  unsigned arrayLen;
}osInputData;

void *createShmBlock(const char *path, unsigned size){

    int memFd=shm_open(path,O_RDWR|O_CREAT,0600);
     check_error(memFd!=-1,"open");
    
    check_error(ftruncate(memFd,size)!=-1,"trunc");
   
    void *addr;
      addr=mmap(0,size,PROT_READ|PROT_WRITE,MAP_SHARED,memFd,0);
    check_error(addr!=MAP_FAILED,"mmap");
   
    close(memFd);
    return addr;
}

            
int main(int argc,char **argv){
       
    check_error(argc==2,"args");
    
    unsigned size=sizeof(osInputData);
    
    osInputData *x=createShmBlock(argv[1],size);
    int i;
    check_error(sem_init(&(x->inDataReady),1,0)!=-1,"sem");
     
     
     scanf("%u",&(x->arrayLen));
     
     for(i=0;i<x->arrayLen;i++){
        scanf("%f",&x->array[i]);
     }
     
     
     check_error(sem_post(&(x->inDataReady))!=-1,"psot"); 
     
     
     printf("%u\n",x->arrayLen);
     for(i=0;i<x->arrayLen;i++){
        printf("%.1f ",x->array[i]);
     }
     printf("\n");  
     
     check_error(munmap(x,size)!=-1,"unmap");      
    exit(EXIT_SUCCESS);
}




