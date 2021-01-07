#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

#include<string.h>
#include<ftw.h>
#include<stdbool.h>

#define check_error(expr,userMsg)\
                  do{\
                  if(!(expr)){\
                   fprintf(stderr,"%s\n",userMsg);\
                   exit(EXIT_FAILURE);\
                   }\
                  }while(0);

void osMkPublicDir(const char *dname){
  mode_t oldmask=umask(0);
  mode_t mode=0777;
 check_error(mkdir(dname,mode)!=-1,"mkdir fail");
  umask(oldmask);
}


int main(int argc,char **argv){
  check_error(argc==2,"argumenti");
  
  osMkPublicDir(argv[1]);

exit(EXIT_SUCCESS);
}








