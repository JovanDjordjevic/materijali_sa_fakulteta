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
#define MAX_SIZE 1024
            
int main(int argc,char **argv){

int par2cld[2];
 check_error(pipe(par2cld)!=-1,"pipe fail");
 
 pid_t pid=fork();
 
 if(pid>0){//parent
     close(par2cld[RD_END]);
     
     char *msg="message";
     int x=12412512;
     
     FILE *in=fdopen(par2cld[WR_END],"w");
        check_error(in!=NULL,"fd open fail");
        
     fprintf(in,"%s %d\n",msg,x);
     
     fclose(in);     
 }
 else if(pid==0){//child
   close(par2cld[WR_END]);
    FILE *in=fdopen(par2cld[RD_END],"r");
      check_error(in!=NULL,"fd open fail child");
      
      char msg[MAX_SIZE];
      int x;
      
    fscanf(in,"%s %d",msg,&x);   
    printf("%s %d\n",msg,x);
   
   fclose(in);  
   exit(EXIT_SUCCESS);
 }
 else{
   check_error(0,"else");
 }

check_error(wait(NULL)!=-1,"wait");

 exit(EXIT_SUCCESS);
}



















