#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<signal.h>

#define check_error(expr,userMsg)\
             do{\
               if(!(expr)){\
                 fprintf(stderr,"%s\n",userMsg);\
                 exit(EXIT_FAILURE);\
                }\
              }while(0);

int s1caught=0;
int s2caught=0;
int sigterm=0;

void sigHandler(int signum){
  
   switch(signum){
   
      case SIGUSR1: s1caught+=1; break;
      case SIGUSR2: s2caught+=1; break;
      case SIGTERM: if(s1caught==2 && s2caught==5){
                           printf("%d %d\n",s1caught,s2caught);
                           exit(EXIT_FAILURE);    //ovo je exit code 0
                       }
                       else exit(EXIT_SUCCESS);  //ovo je exit code 1
      default: break;
   }


}


int main(int argc,char **argv){
   
    // printf("pid: %d\n",(int)getpid());
   
   while(1){
     
     check_error(signal(SIGUSR1,sigHandler)!=SIG_ERR,"signal 1 fail");
     check_error(signal(SIGUSR2,sigHandler)!=SIG_ERR,"signal 1 fail");
     check_error(signal(SIGTERM,sigHandler)!=SIG_ERR,"signal 1 fail");  
   
   }
  
  exit(EXIT_SUCCESS);
}





