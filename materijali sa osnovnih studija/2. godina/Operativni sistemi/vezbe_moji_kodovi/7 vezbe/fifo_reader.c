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
  
  int fd=open(argv[1],O_RDONLY);
    check_error(fd!=-1,"open fail");
   
   char buffer[MAX_SIZE];
   
   do{
       int bytesRead=0;
       bytesRead=read(fd,buffer,MAX_SIZE);
         check_error(bytesRead!=-1,"read failed");
      if(bytesRead==0) break;
      
      buffer[bytesRead]='\0';
      
      printf("%s\n",buffer);
      
   }while(1);
  
  exit(EXIT_SUCCESS);
}


