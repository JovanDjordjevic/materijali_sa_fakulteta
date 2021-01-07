#include<stdio.h>
#include<stdlib.h>

#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<string.h>

#define check_error(expr,userMsg)\
         do{\
           if(!(expr)){\
            fprintf(stderr,"%s\n",userMsg);\
            exit(EXIT_FAILURE);\
            }\
           }while(0);

#define MAX_SIZE 256


int main(int argc,char **argv){
  
    check_error(argc==2,"argumenti");
  
    check_error(mkfifo(argv[1],0644)!=-1,"mkfifo failed")
  
  int fd=open(argv[1],O_WRONLY);
    check_error(fd!=-1,"open fail");
    
  char buffer[MAX_SIZE];
  
  do{
     scanf("%s",buffer);
     check_error(write(fd,buffer,strlen(buffer))!=-1,"write failed");
     
     printf("continue? yes/no\n");
     scanf("%s",buffer);
     
     if(!strcasecmp("no",buffer)){
       break;
     }
  
  }while(1);
  
  close(fd);  
  
  exit(EXIT_SUCCESS);
}





















