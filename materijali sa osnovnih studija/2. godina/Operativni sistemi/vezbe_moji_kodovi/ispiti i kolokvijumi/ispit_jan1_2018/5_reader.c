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
#include<ctype.h>
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

void *getBlock(const char *path,unsigned *size){
  
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
   
   unsigned size;
   OsInputData *data=getBlock(argv[1],&size);
   
   check_error(sem_wait(&(data->inDataReady))!=-1,"wait");
   
   unsigned len=strlen(data->str);
   int i;
   for(i=0;i<len;i++){
     if(isupper(data->str[i])) data->str[i]=tolower(data->str[i]); 
     else data->str[i]=toupper(data->str[i]);
   }
   printf("%s\n",data->str);
   
   check_error(sem_post(&(data->dataProcessed))!=-1,"post");
   
   check_error(munmap(data,size)!=-1,"munmap");

  exit(EXIT_SUCCESS);
}
                 
