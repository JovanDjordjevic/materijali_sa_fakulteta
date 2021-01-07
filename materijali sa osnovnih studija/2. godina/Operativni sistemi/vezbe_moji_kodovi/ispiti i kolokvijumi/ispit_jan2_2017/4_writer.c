//kod deluje okej ali iz nekog razloga ne pravi shm fajl na putanji,
//pa samim tim ne mogu da testiram 4_reader koji deluje da radi

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
#define check_thread(err,userMsg)\
          do{\
            int _err=err;\
            if(_err){\
              errno=_err;\
              check_error(0,userMsg);\
             }\
            }while(0);
#define MAX_STR_LEN 256

typedef struct{
  sem_t inDataReady;
  sem_t outDataReady;
  char s[MAX_STR_LEN];
}osInputData;

void* createShmBlock(const char* path,unsigned size){
  
  int memFd=shm_open(path,O_RDWR | O_CREAT,0600);
    check_error(memFd!=-1,"shm open");
  
  check_error(ftruncate(memFd,size)!=-1,"trunc");
  
  void *addr;
  addr=mmap(0,size,PROT_READ | PROT_WRITE,MAP_SHARED,memFd,0);
    check_error(addr!=MAP_FAILED,"mmap") 
  
  close(memFd);
  return addr;
}
            
int main(int argc,char **argv){
       
       check_error(argc==2,"args");
  
    unsigned size=sizeof(osInputData);
      
   osInputData *array=createShmBlock(argv[1],size);
   
   
   check_error(sem_init(&(array->inDataReady),1,1)!=-1,"sem init in");
   check_error(sem_init(&(array->outDataReady),1,0)!=-1,"sem init out");
      
   check_error(sem_wait(&(array->inDataReady))!=-1,"sem wait");
   
    strcpy(array->s,"abcdefg");
   
   check_error(sem_post(&(array->outDataReady))!=-1,"post wait");
   
   check_error(munmap(array,size)!=-1,"munamp");
   check_error(shm_unlink(argv[1])!=-1,"unlink");
      
    exit(EXIT_SUCCESS);
}





