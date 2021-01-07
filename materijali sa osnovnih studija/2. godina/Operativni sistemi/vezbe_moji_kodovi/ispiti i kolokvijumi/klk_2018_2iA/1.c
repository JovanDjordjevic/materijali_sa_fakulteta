#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

#include<utime.h>

#define check_error(expr,userMsg)\
                  do{\
                  if(!(expr)){\
                   fprintf(stderr,"%s\n",userMsg);\
                   exit(EXIT_FAILURE);\
                   }\
                   }while(0);


int main(int argc,char* argv[]){
  check_error(argc==3,"argumenti");
 int sekunde=atoi(argv[2]);
 struct stat fInfo;
  check_error(stat(argv[1],&fInfo)!=-1,"stat fail");
  
  struct utimbuf t;
   t.actime=(time_t)sekunde;
   t.modtime=(time_t)sekunde;
check_error(utime(argv[1],&t)!=-1,"utime fail");

exit(EXIT_SUCCESS);
}













