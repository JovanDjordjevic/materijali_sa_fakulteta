#include<stdio.h>
#include<stdlib.h>


#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

#include<utime.h>

#define MAXSIZE 1024
#define check_error(expr,userMsg)\
                  do{\
                  if(!(expr)){\
                   fprintf(stderr,"%s\n",userMsg);\
                   exit(EXIT_FAILURE);\
                   }\
                   }while(0);


int main(int argc,char* argv[]){

check_error(argc==2,"argumenti");

struct stat fInfo;
check_error(stat(argv[1],&fInfo)!=-1,"stat fail");

FILE *f=fopen(argv[1],"w");
check_error(f!=NULL,"fopen");
fclose(f);

struct utimbuf t;
t.actime=fInfo.st_atime;
t.modtime=fInfo.st_mtime;

check_error(utime(argv[1],&t)!=-1,"utime fail");

exit(EXIT_SUCCESS);
}













