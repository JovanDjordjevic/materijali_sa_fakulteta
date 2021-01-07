#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

#include<string.h>
#include<errno.h>

#define check_error(expr,userMsg)\
                  do{\
                  if(!(expr)){\
                   fprintf(stderr,"%s\n",userMsg);\
                   exit(EXIT_FAILURE);\
                   }\
                  }while(0);
                  


int main(int argc,char **argv){
  check_error(argc==4,"argumenti");
  
    long privileges=strtol(argv[3],NULL,8);
     mode_t oldmask=umask(0);
    
    if(!strcmp(argv[1],"-f")){

      int fd=open(argv[2],O_RDWR|O_CREAT|O_EXCL,privileges);
          if(fd==-1){
           if(errno==EEXIST){
             check_error(chmod(argv[2],privileges)!=-1,"chmod fail");
          }
          else check_error(0,"open fail");
      }
     }
      
    else if(!strcmp(argv[1],"-d")){
      int dir=mkdir(argv[2],privileges);
        if(dir==-1){
         if(errno==EEXIST){
             check_error(chmod(argv[2],privileges)!=-1,"chmod fail");
          }else check_error(0,"mkdir fail");
     }
    }

    else check_error(0,"else");  

umask(oldmask);
exit(EXIT_SUCCESS);
}








