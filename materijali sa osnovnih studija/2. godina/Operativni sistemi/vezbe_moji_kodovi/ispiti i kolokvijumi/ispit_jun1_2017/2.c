//na grejderu ne radi za nepostojeci.txt ali kod mene radi

#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<sys/wait.h>
#include<pthread.h>
#include<errno.h>

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
        check_error(pid!=-1,"fork failed");
      
      if(pid==0){//child
         close(cld2par[RD_END]);
         
         check_error(dup2(cld2par[WR_END],STDOUT_FILENO)!=-1,"dup2 failed");
         check_error(execlp("ls","ls","-l",argv[1],NULL)!=-1,"execlp");
         
         close(cld2par[WR_END]);
         exit(EXIT_SUCCESS);
      }
     
     //parent
     
         close(cld2par[WR_END]);
         char buf[MAX_SIZE];
         int readBytes=0;
         readBytes=read(cld2par[RD_END],buf,MAX_SIZE);
           check_error(readBytes!=-1,"read failed");
         close(cld2par[RD_END]);      
      
      int status=0;
        check_error(waitpid(pid,&status,0)!=-1,"wait");
      
      if(WIFEXITED(status)){
        if(WEXITSTATUS(status)!=EXIT_SUCCESS){
          printf("Neuspeh\n");
          exit(EXIT_FAILURE);}
      }
      else{
        printf("Neuspeh\n");
        exit(EXIT_FAILURE);
      }    
     
     char rez[11];
     sscanf(buf,"%s",rez);
     printf("%s\n",rez);
     
  exit(EXIT_SUCCESS);
}





