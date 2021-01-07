#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>

#define check_error(expr,usrMsg)\
            do{\
              if(!(expr)){\
                fprintf(stderr,"%s\n",usrMsg);\
                exit(EXIT_FAILURE);\
              }\
            }while(0);


int main(int argc,char **argv){
   check_error(argc==2,"argumenti");
  struct stat fInfo;
   check_error(stat(argv[1],&fInfo)!=-1,"stat fail");
   check_error(!S_ISDIR(fInfo.st_mode),"dir");
  time_t t=abs(fInfo.st_atime-fInfo.st_mtime)/86400;
  
  fprintf(stdout,"%ld",t);
   
 exit(EXIT_SUCCESS);
}
