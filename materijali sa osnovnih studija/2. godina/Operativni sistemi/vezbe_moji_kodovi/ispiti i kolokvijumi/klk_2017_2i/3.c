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
#include<time.h>

#define check_error(expr,userMsg)\
                  do{\
                  if(!(expr)){\
                   fprintf(stderr,"%s\n",userMsg);\
                   exit(EXIT_FAILURE);\
                   }\
                  }while(0);

unsigned osNumOfDaysFileModified(const char *fpath){
 struct stat fInfo;
 check_error(stat(fpath,&fInfo)!=-1,"stat fail");
 time_t now=time(NULL);
 time_t t= now-fInfo.st_mtime;
 
 return t/86400;
}


int main(int argc,char **argv){
  check_error(argc==2,"argumenti");
  unsigned days=osNumOfDaysFileModified(argv[1]);
  fprintf(stdout,"%u\n",days);
 
exit(EXIT_SUCCESS);
}








