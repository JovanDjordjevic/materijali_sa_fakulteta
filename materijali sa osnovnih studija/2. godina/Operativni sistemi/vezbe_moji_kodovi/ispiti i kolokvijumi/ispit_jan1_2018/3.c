#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

#include<errno.h>
#include<time.h>
#include<string.h>
#include<sys/wait.h>

#define check_error(expr,userMsg)\
                do{\
                  if(!(expr)){\
                    fprintf(stderr,"%s\n",userMsg);\
                    exit(EXIT_FAILURE);\
                   }\
                 }while(0);

#define RD_END (0)
#define WR_END (1)


int main(int argc, char **argv){

  check_error(argc==3,"args");
   
   if( (strcmp(argv[2],"-w"))!=0 && (strcmp(argv[2],"-c"))!=0 &&  (strcmp(argv[2],"-l"))!=0 ){
     check_error(0,"opcija");
   }
  int cld2par[2];
    check_error(pipe(cld2par)!=-1,"pipe");
  
  
  pid_t pid=fork();
    check_error(pid!=-1,"fork");
  
  if(pid>0){//parent
     close(cld2par[WR_END]);
     
     FILE *in=fdopen(cld2par[RD_END],"r");
       check_error(in!=NULL,"fdopen");
     
     char *line=NULL;
     size_t size;
     while(getline(&line,&size,in)!=-1){
        
        printf("%s",line);
     }
      
     fclose(in); 
     close(cld2par[RD_END]); 
  }
  else if(pid==0){//child
    close(cld2par[RD_END]);
    
    check_error(dup2(cld2par[WR_END],STDOUT_FILENO)!=-1,"dup2");
    
    check_error(execlp("wc","wc",argv[2],argv[1],NULL)!=-1,"exec");
    
    close(cld2par[WR_END]);
  }    
    
  int status;
  check_error(wait(&status)!=-1,"wait");
  
  if(WIFEXITED(status)){
     if(WEXITSTATUS(status)!=EXIT_SUCCESS){
       printf("Neuspeh\n");
       exit(EXIT_FAILURE);
      }
     else exit(EXIT_SUCCESS); 
       
  }
  else {
    printf("Neuspeh\n");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
                 
