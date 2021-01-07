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
           
#define RD_END (0)
#define WR_END (1)
            
int main(int argc,char **argv){

int cld2par[2];
 check_error(pipe(cld2par)!=-1,"pipe fail");
 
 pid_t pid=fork();
 
 if(pid>0) {//parent
     close(cld2par[WR_END]);
     
      char *line=NULL;
      size_t lineLen=0;
      int lineCount=0;
      
     FILE *f=fdopen(cld2par[RD_END],"r");
       check_error(f!=NULL,"open fail");
     
     while(getline(&line,&lineLen,f)!=-1){
       lineCount++;
       printf("%d %s",lineCount,line);
     }  
   free(line);
   fclose(f);
 }
 else if(pid==0) {//child
   close(cld2par[RD_END]);
   
   check_error(dup2(cld2par[WR_END],STDOUT_FILENO)!=-1,"dup 2 fail");
   check_error(execlp("ls","ls","-l",NULL)!=-1,"execlp fail");
   
    
 exit(EXIT_SUCCESS);
 }
 else 
 check_error(0,"esle");
 
 int status=0;
 check_error(wait(&status)!=-1,"wait failed");
 
 if(WIFEXITED(status) && WEXITSTATUS(status)==EXIT_SUCCESS){
   printf("all ok\n");
 }
 else {
   printf("not ok\n");
 }

 exit(EXIT_SUCCESS);
}



















