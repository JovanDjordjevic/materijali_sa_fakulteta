#define _XOPEN_SOURCE 700
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
           

void *createShmBlock(const char *path, unsigned size){
   
   int memFd=shm_open(path,O_RDWR | O_CREAT,0600);
     check_error(memFd!=-1,"shm open fail");
     
     check_error(ftruncate(memFd,size)!=-1,"ftruncate failed");
     
     void *addr;
     
     addr=mmap(NULL,size,PROT_READ | PROT_WRITE,MAP_SHARED,memFd,0);
     
     check_error(addr!=MAP_FAILED,"mmap fail");
     
     close(memFd);
     return addr;
}



int main(int argc,char **argv){
  
    check_error(argc==2,"argumenti");
    
    int memSize=sizeof(int)*10;
    int *array=createShmBlock(argv[1],memSize);
    
    int i;
    for(i=0; i<10; i++){
       array[i]=i;
    }
  
  check_error(munmap(array,memSize)!=-1,"unmap failed");
  
  
  exit(EXIT_SUCCESS);
}




















