#include<stdio.h>
#include<stdlib.h>

#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<sys/wait.h>

#define check_error(expr,userMsg)\
         do{\
           if(!(expr)){\
            fprintf(stderr,"%s\n",userMsg);\
            exit(EXIT_FAILURE);\
            }\
           }while(0);


int main(int argc,char **argv){

check_error(argc==3,"argumenti");

pid_t pid=fork();

  if(pid==0){//child
    
    check_error(execlp("gcc","gcc","-std=c99",argv[1],"-o",argv[2],NULL)!=-1,"execlp failed");
           
    exit(EXIT_SUCCESS);
  }
   
   
   int status=0;
   check_error(waitpid(-1,&status,0)!=-1,"waitpid fail");
   
   if(WIFEXITED(status)){
       
       if(WEXITSTATUS(status)==EXIT_SUCCESS){
          printf("prevodjenje uspesno\n");
       }
       else{
          printf("prevodjenje neuspesno\n");       
       }
   }

  exit(EXIT_SUCCESS);
}

