#include<stdio.h>
#include<stdlib.h>

#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<sys/mman.h>

#define check_error(expr,userMsg)\
         do{\
           if(!(expr)){\
            fprintf(stderr,"%s\n",userMsg);\
            exit(EXIT_FAILURE);\
            }\
           }while(0);

#define MAX_SIZE 256           

typedef struct{
  int niz[MAX_SIZE];
  int n;
}shmData_t;

void *getShmBlock(const char* path,unsigned *size){
  
  int memFd=shm_open(path,O_RDWR,0600);
    check_error(memFd!=-1,"shm_open fail");
  
  struct stat fInfo;
  check_error(fstat(memFd,&fInfo)!=-1,"stat fail");
  
  *size=fInfo.st_size;  
  
  void *addr;
  addr=mmap(NULL,*size,PROT_READ | PROT_WRITE, MAP_SHARED,memFd,0);
    check_error(addr!=MAP_FAILED,"mmap failed");
  
  close(memFd);
  
  return addr;
}


int main(int argc,char **argv){
  
   check_error(argc==2,"argumenti");
  
   unsigned size=0;   
   shmData_t *array=getShmBlock(argv[1],&size);
   
   int i;
   for(i=0;i<(array->n);i++){
     printf("%d ",array->niz[i]);
   }
   printf("\n");
   
   check_error(munmap(array,size)!=-1,"unmap failed");
  
  exit(EXIT_SUCCESS);
}


