#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

#define check_error(expr,usrMsg)\
            do{\
              if(!(expr)){\
                fprintf(stderr,"%s\n",usrMsg);\
                exit(EXIT_FAILURE);\
              }\
            }while(0);


int main(int argc,char **argv){
  check_error(argc==4,"argumenti");
   long privileges=strtol(argv[3],NULL,8);
   long oldmask=umask(0);
  if(!strcmp(argv[1],"-f")){
    int fd=open(argv[2],O_RDONLY|O_CREAT|O_EXCL,privileges);
      if(fd==-1){
         if(errno==EEXIST) {
           close(fd);
           exit(EXIT_FAILURE);
         }
        close(fd);
           exit(EXIT_FAILURE);
      }
 }
  else if(!strcmp(argv[1],"-d")){
    int dir=mkdir(argv[2],privileges);
    check_error(dir!=-1,"mkdir");
  }
  else check_error(0,"else");  
   
   umask(oldmask); 
 exit(EXIT_SUCCESS);
}
