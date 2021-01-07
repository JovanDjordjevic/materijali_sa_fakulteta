#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#include<errno.h>
#include<pthread.h>
#include<string.h>
#include<sys/wait.h>

#define check_error(expr,userMsg)\
                do{\
                  if(!(expr)){\
                     fprintf(stderr,"%s\n",userMsg);\
                     exit(EXIT_FAILURE);\
                    }\
                  }while(0);
                  
#define check_thread(err,userMsg)\
                do{\
                  int _err=err;\
                  if(_err){\
                    errno=_err;\
                    check_error(0,userMsg);\
                   }\
                  }while(0);
#define RD_END (0)
#define WR_END (1)

                  
int main(int argc, char **argv){
     
     int cld2par[2];
       check_error(pipe(cld2par)!=-1,"pipe");
      
     pid_t pid=fork();
       check_error(pid!=-1,"arg");
     
     
     if(pid>0){//parent
         close(cld2par[WR_END]);
         
         FILE *in=fdopen(cld2par[RD_END],"r");
           check_error(in!=NULL,"fdopen");
           
           fscanf(in,"%*s %*d ");
           char *line=NULL;
           size_t size=0;
           
           while(getline(&line,&size,in)!=-1){
              char  rez[10];
              sscanf(line,"%*s %*d %*s %*s %*d %*s %*d %s %*s",rez);
              printf("%s\n",rez);
           }          
         
         close(cld2par[RD_END]);
     }
     else if(pid==0){//child
         close(cld2par[RD_END]);
         
         check_error(dup2(cld2par[WR_END],STDOUT_FILENO)!=-1,"dup");
         
         check_error(execlp("ls","ls","-l",argv[1],NULL)!=-1,"exec");
                     
         close(cld2par[WR_END]);        
     }
 
  exit(EXIT_SUCCESS);
}
