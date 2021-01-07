#define _XOPEN_SOURCE 700    //kako testirati ovaj program?
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

#include<string.h>
#include<errno.h>

#define check_error(expr,userMsg)\
           do{\
             if(!(expr)){\
               fprintf(stderr,"%s\n",userMsg);\
               exit(EXIT_FAILURE);\
             }\
           }while(0);
           
int checkFifoR(const char *path){

 int fd=open(path,O_WRONLY | O_NONBLOCK);
   if(fd==-1){   
     if(errno==ENXIO)  return 0;
     else check_error(0,"fd pukao zbog else");   
   }

close(fd);
return 1;
}           


int checkFifoW(const char *path){

  int fd=open(path,O_RDONLY | O_NONBLOCK);
    check_error(fd!=-1,"W open ");
    
    char c;
    int retVal=read(fd,&c,1);
    
    if(retVal==0){   //stigli do EOF, to je dozvoljeno
      close(fd);
      return 0;
    }
    else if(retVal<0){    //greska
       if(errno==EAGAIN){  //zbog toga sto bi blokiralo
        close(fd);
        return 1;
       }
    }
    else{
      check_error(0,"W else")  //drugi razlog pucanja
    }
    
  close(fd);  //neko je otvorio fifo u W modu i nesto upisao
  return 1;  
}
           
int main(int argc,char **argv){

  check_error(argc==3,"argumenti");
  
  if(argv[2][0]=='r'){
     int retVal=checkFifoR(argv[1]);
     printf("has read end:%s\n",retVal ? "da" :"ne");
  }
  else if(argv[2][0]=='w'){
     int retVal=checkFifoW(argv[1]);
     printf("has write end: %s\n",retVal ? "da" : "ne");  
  }
  else
     check_error(0,"else");

 exit(EXIT_SUCCESS);
}



















