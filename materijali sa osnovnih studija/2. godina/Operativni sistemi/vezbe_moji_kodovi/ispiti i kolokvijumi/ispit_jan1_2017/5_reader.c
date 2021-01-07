//izgleda isti kod ko njegov ali na grejderu samo 10%
//za 9/10 primera vraca pogresan exit code;

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

void *getShmBlock(const char *path, unsigned *size){
    int memFd=shm_open(path,O_RDWR,0600);
     check_error(memFd!=-1,"open");
    
   struct stat fInfo;
     check_error(fstat(memFd,&fInfo)!=-1,"stat");
    *size=fInfo.st_size; 
    
    void *addr;
      addr=mmap(0,*size,PROT_READ|PROT_WRITE,MAP_SHARED,memFd,0);
    check_error(addr!=MAP_FAILED,"mmap");
    
    close(memFd);
    return addr;
}

            
int main(int argc,char **argv){
       
    check_error(argc==2,"args");
    
    unsigned size=0;  
    
    osInputData *x=getShmBlock(argv[1],&size);  
    
    check_error(sem_wait(&(x->inDataReady))!=-1,"sem wait");
     
     int i,j; 
     for(i=0;i<x->arrayLen;i++){
        for(j=i+1;j<x->arrayLen;j++){
           
           if(x->array[i] > x->array[j]){
                float temp=x->array[i];
                x->array[i]=x->array[j];
                x->array[j]=temp;
             }
        }
     }
     printf("%.1f\n",x->array[(x->arrayLen)/2]); 
     
     //check_error(sem_post(&(x->inDataReady))!=-1,"sem psot"); 
     //u njegovom zadatku nema sem post
     
     check_error(munmap(x,size)!=-1,"unmap"); 
          
    exit(EXIT_SUCCESS);
}




