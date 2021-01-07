#include<stdio.h>
#include<stdlib.h>

#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<stdint.h>
#include<sys/wait.h>


#define check_error(expr,userMsg)\
         do{\
           if(!(expr)){\
            fprintf(stderr,"%s\n",userMsg);\
            exit(EXIT_FAILURE);\
            }\
           }while(0);
           
int main(int argc,char **argv){


pid_t childPid = fork();
  check_error(childPid!=-1,"fork fail");
  
  if(childPid>0){//parent
  
    printf("ovo ispisuje parent\n");
    printf("pid ovog procesa %jd, child pid %jd\n",(intmax_t)getpid,(intmax_t)childPid);
  
  }
  else if(childPid==0){ //child
  
  printf("ovo ispisuje samo child\n");
  printf("pid ovog procesa %jd, pid njegovog parenta:%jd\n ",(intmax_t)getpid,(intmax_t)getppid);
  
  exit(EXIT_SUCCESS);
  }
  
  else 
    check_error(0,"else");
  
  check_error(wait(NULL)!=-1,"wait fail");
  
  printf("ovo na krajus tampa samo parent\n");
  


  exit(EXIT_SUCCESS);
}

