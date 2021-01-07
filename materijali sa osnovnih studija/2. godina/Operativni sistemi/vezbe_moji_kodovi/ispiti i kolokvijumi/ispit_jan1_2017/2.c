//na grejderu ne prolazi test primer nepostojeci.txt a kod mene proalzi

#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<sys/wait.h>
#include<string.h>

#define check_error(expr,userMsg)\
             do{\
               if(!(expr)){\
                 fprintf(stderr,"%s\n",userMsg);\
                 exit(EXIT_FAILURE);\
                }\
              }while(0);

#define MAX_SIZE 1024
#define RD_END (0)
#define WR_END (1)

int main(int argc,char **argv){
   check_error(argc==2,"argumenti");
   
   int cld2par[2];
   check_error(pipe(cld2par)!=-1,"pipe failed");
   
   pid_t pid=fork();
   if(pid>0){//parent
      close(cld2par[WR_END]);
      
      FILE *in=fdopen(cld2par[RD_END],"r");
        check_error(in!=NULL,"fdopen");
            
      char buf[MAX_SIZE];
      fscanf(stderr,"%s",buf);
      int x;
      
      if(strlen(buf)>0 && (fscanf(in,"%d",&x)!=1)){   //!!!!
            fprintf(stdout,"Neuspeh");
            exit(EXIT_FAILURE);
         }
      else {
       fprintf(stdout,"%d",x);
      }                               
      
      fclose(in);
      close(cld2par[RD_END]);
   }
   else if(pid==0){//child
      close(cld2par[RD_END]);      
      
      check_error(dup2(cld2par[WR_END],STDERR_FILENO)!=-1,"dup2 fail");  //!!!!
      check_error(dup2(cld2par[WR_END],STDOUT_FILENO)!=-1,"dup2 failed");
      check_error(execlp("stat","stat","--format","%s",argv[1],NULL)!=-1,"execlp fail");     
      
      close(cld2par[WR_END]);
   exit(EXIT_SUCCESS);
   }
   else 
      {check_error(0,"else");}
      
      
  int status;
  check_error(wait(&status)!=-1,"wait failed");
  
  
  if(WIFEXITED(status)){
     if(WEXITSTATUS(status)==EXIT_FAILURE) printf("Neuspeh\n");
     //else printf("all ok\n");
  }

  
  exit(EXIT_SUCCESS);
}





