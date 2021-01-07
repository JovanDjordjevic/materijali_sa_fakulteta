
//isti kod kao njegov ali ne radi ni jedan ni drugi

#define _XOPEN_SOURCE 700     
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

#include<string.h>
#include<errno.h>
#include<sys/wait.h>

#define check_error(expr,userMsg)\
           do{\
             if(!(expr)){\
               fprintf(stderr,"%s\n",userMsg);\
               exit(EXIT_FAILURE);\
             }\
           }while(0);
           

            
int main(int argc,char **argv){

check_error(setvbuf(stdout,NULL,_IOFBF,0)==0,"setvbuf fail");

printf("%s\n","neka poruka");

int fd=open("bean.txt",O_WRONLY | O_CREAT | O_TRUNC,0644);
  check_error(fd!=-1,"open failed");

int stdoutCpy=dup(STDOUT_FILENO);
  check_error(stdoutCpy!=-1,"dup fail");
  
check_error(dup2(fd,STDOUT_FILENO)!=-1,"dup 2 fail");
   printf("poruka ide u fajl\n");  

check_error(dup2(stdoutCpy,STDOUT_FILENO)!=-1,"dup 2 fail");
 printf("poruka za konzolu");

close(fd);

 exit(EXIT_SUCCESS);
}



















