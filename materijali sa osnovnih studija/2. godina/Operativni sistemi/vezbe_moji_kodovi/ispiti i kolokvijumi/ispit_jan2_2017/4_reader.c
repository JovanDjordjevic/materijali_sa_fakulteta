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

void* getShmBlock(const char* path,unsigned *size){
  
  int memFd=shm_open(path,O_RDWR,0600);
    check_error(memFd!=-1,"shm open");
  
  struct stat fInfo;
   check_error(fstat(memFd,&fInfo)!=-1,"stat");
  
  (*size)=fInfo.st_size;
  
  void *addr;
  addr=mmap(0,*size,PROT_READ | PROT_WRITE,MAP_SHARED,memFd,0);
    check_error(addr!=MAP_FAILED,"mmap") 
  
  close(memFd);
  return addr;
}
            
int main(int argc,char **argv){
       
       check_error(argc==3,"args");
   
   int br=atoi(argv[2]);
    br=br%26;
    
   unsigned size;      
   osInputData *array=getShmBlock(argv[1],&size);
   
   int n=strlen(array->s);
   int i;   
   check_error(sem_wait(&(array->outDataReady))!=-1,"sem wait");
   
     for(i=0;i<n;i++){
        array->s[i]+=br;
     }
   
   check_error(sem_post(&(array->inDataReady))!=-1,"post wait");
   
   
   printf("%s\n",array->s);
   
   check_error(munmap(array,size)!=-1,"munamp");

      
    exit(EXIT_SUCCESS);
}




