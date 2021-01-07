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
#include<signal.h>
#include<ctype.h>
#include<semaphore.h>
#include<sys/mman.h>
#include<sys/poll.h>
#include<limits.h>
#include<stdint.h>

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
#define ARRAY_MAX (1024)


int main(int argc, char **argv){
    
   check_error(argc==2,"args");
   
   int cld2par[2];
     check_error(pipe(cld2par)!=-1,"pipe");
   
   char *ext=argv[1];
   
   pid_t pid=fork();
     check_error(pid!=-1,"fork");
     
   if(pid>0){//parent
     close(cld2par[WR_END]);
     
     FILE *in=fdopen(cld2par[RD_END],"r");
       check_error(in!=NULL,"fdopen");
     
     int count=0;
     char *line=NULL;
     size_t size=0;
     while(getline(&line,&size,in)!=-1){
        
        line[strlen(line)-1]='\0';   //strcmp je pucao zato sto se u liniji posle npr .c javljaju jos neki spejsovi i \n pa tek onda \0, ovako mi pomerimo \0 za jedno mesto u nazad da eliminisemo \n i omogucimo strcmp 
        char *ptr=strrchr(line,'.');
        
        if(!strcmp(ptr,ext)) {
          count++;
        }
        //printf("%s\n",ptr);
     }
     
     printf("%d\n",count);
     
     fclose(in);
     close(cld2par[RD_END]);
   }
   else if(pid==0){//child
     close(cld2par[RD_END]);
     
     check_error(dup2(cld2par[WR_END],STDOUT_FILENO)!=-1,"dup");
     check_error(execlp("find","find",".","-type","f",NULL)!=-1,"exec failed");
       
     close(cld2par[WR_END]);
   }
   
     
   
   
  exit(EXIT_SUCCESS);
}
