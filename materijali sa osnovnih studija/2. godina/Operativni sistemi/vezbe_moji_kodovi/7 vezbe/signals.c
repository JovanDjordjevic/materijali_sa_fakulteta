#include<stdio.h>
#include<stdlib.h>

#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<sys/wait.h>
#include<signal.h>

#define check_error(expr,userMsg)\
         do{\
           if(!(expr)){\
            fprintf(stderr,"%s\n",userMsg);\
            exit(EXIT_FAILURE);\
            }\
           }while(0);
           
int sigcaught=0;
int termcaught=0;

void signalHandler(int signum){
  
  switch(signum){
    case SIGINT: sigcaught=1; break;
    case SIGTERM: termcaught=1; break; 
    default: break;
  }
  
}

int main(int argc,char **argv){
  
  printf("PID: %d\n",(int)getpid());
  
  do{
     check_error(signal(SIGINT,signalHandler)!=SIG_ERR,"sigusr fail");
     check_error(signal(SIGTERM,signalHandler)!=SIG_ERR,"sigterm fail");
  
  pause();
  
  if(sigcaught){
    printf("SIGINT caught\n");
    sigcaught=0;
  }
  
  }while(!termcaught);
  
  
  exit(EXIT_SUCCESS);
}





















