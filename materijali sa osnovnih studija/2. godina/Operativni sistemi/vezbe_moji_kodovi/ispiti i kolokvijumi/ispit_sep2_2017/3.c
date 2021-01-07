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
    
      char *line=NULL;
      size_t size=0; 
   
   while(getline(&line,&size,stdin)!=-1){
     
     int cld2par[2];
       check_error(pipe(cld2par)!=-1,"pipe");      
     char x[15],y[15];
     char op[5]; 
      
      sscanf(line,"%s%s%s",x,y,op);
      
      pid_t pid=fork();                      //fork 
        check_error(pid!=-1,"fork failed");
      
      if(pid>0){//parent
         close(cld2par[WR_END]);
         
         FILE *in=fdopen(cld2par[RD_END],"r");
          check_error(in!=NULL,"fopen");
          
         int a;
         fscanf(in,"%d",&a);
         printf("%d\n",a); 
          
         fclose(in);
         close(cld2par[RD_END]);     
      }
      else if(pid==0){//child
         close(cld2par[RD_END]);
          
          check_error(dup2(cld2par[WR_END],STDOUT_FILENO)!=-1,"dup 2 failed");
           
           //fprintf(stderr,"%d %c %d\n",x,op,y);
           
          check_error(execlp("expr","expr", x, op, y,NULL)!=-1,"exec");
           //ONO STO SALJEMO EXECU KAO ARGUMENTE MORAJU BITI STRINGOVI A NE BROJEVNI TIPOVI KAO STO SAM STAVLJAO PRE          
         close(cld2par[WR_END]);
      } 
      
      check_error(wait(NULL)!=-1,"wait");
           
   }

 
  exit(EXIT_SUCCESS);
}
