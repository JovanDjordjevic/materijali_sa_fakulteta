#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

#include<string.h>
#include<errno.h>

#define MAX_SIZE 1024
#define check_error(expr,userMsg)\
                  do{\
                  if(!(expr)){\
                   fprintf(stderr,"%s\n",userMsg);\
                   exit(EXIT_FAILURE);\
                   }\
                  }while(0);
                  


int main(int argc,char **argv){
  check_error(argc==3,"argumenti");
  
  if(!strcmp(argv[1],"-r")){
    int fd=open(argv[2],O_RDONLY);
     check_error(fd!=-1,"open fail");
    char *buffer=malloc(MAX_SIZE);
     check_error(buffer!=NULL,"alokacija");
    int readBytes=0;
     while( (readBytes=read(fd,buffer,MAX_SIZE))>0 ){
       if(write(STDOUT_FILENO,buffer,readBytes)<0){
          free(buffer);
          check_error(0,"write");
       }
     }     
     free(buffer);
     close(fd);
  }
  else if(!strcmp(argv[1],"-w")){
    int fd=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644);
      check_error(fd!=-1,"open fail");
    char *buffer=malloc(MAX_SIZE);
      check_error(buffer!=NULL,"alokacija");
    int readBytes=0;
    while((readBytes=read(STDIN_FILENO,buffer,MAX_SIZE))>0){
      if(write(fd,buffer,readBytes)<0){
        free(buffer);
        check_error(0,"write fail");
      }
    }
    free(buffer);
    close(fd);
  }
  else if(!strcmp(argv[1],"-a")){
    int fd=open(argv[2],O_APPEND|O_CREAT|O_WRONLY,0644);
      check_error(fd!=-1,"open fail");
    char *buffer=malloc(MAX_SIZE);
      check_error(buffer!=NULL,"alokacija");
    int readBytes=0;
    
    while((readBytes=read(STDIN_FILENO,buffer,MAX_SIZE))>0){
      if(write(fd,buffer,readBytes)<0){
         free(buffer);
         check_error(0,"write fail");
      }
    }            
     free(buffer);
     close(fd);      
  }
  else{
   check_error(0,"else");
  }

exit(EXIT_SUCCESS);
}








