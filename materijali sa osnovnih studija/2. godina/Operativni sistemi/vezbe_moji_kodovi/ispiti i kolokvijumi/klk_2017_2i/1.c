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

bool osIsPublicFile(const char *fpath){
   struct stat fInfo;
   check_error(stat(fpath,&fInfo)!=-1,"stat fail");
   check_error(!S_ISDIR(fInfo.st_mode),"pogresan tip fajla");
   
   if( (fInfo.st_mode & S_IROTH) && (fInfo.st_mode & S_IWOTH) && !(fInfo.st_mode & S_IXOTH)) return true;
   else return false;
   
}



int main(int argc,char **argv){
  check_error(argc==2,"argumenti");
  
  bool ret=osIsPublicFile(argv[1]);
   if(ret==true) fprintf(stdout,"true\n");
   else fprintf(stdout,"false\n");

exit(EXIT_SUCCESS);
}








