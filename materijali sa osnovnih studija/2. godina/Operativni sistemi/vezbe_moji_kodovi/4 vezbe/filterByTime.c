#define _XOPEN_SOURCE 700

#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

#include<ftw.h>
#include<time.h>
#include<string.h>

#define chec_error(expr,userMsg) \
    do{\
     if(!(expr)){\
       fprintf(stderr,"%s\n",userMsg);\
       exit(EXIT_FAILURE);\
       }\
      }while(0);
int days=0;
time_t now=0;

int processFile(const char *path, const struct stat *sb, int typeflag,struct FTW *ftwbuf){
  if(typeflag==FTW_F){
     int dif=(now-sb->st_mtime)/86400;
     if(dif<=days) printf("%s\n",path);
  }
return 0;
}
      
      
      
int main(int argc, char **argv){
  check_error(argc==3,"argumenti");
  days=atoi(argv[2]);
  now=time(NULL);
  struct stat fInfo;
  check_error(stat(argv[1],&fInfo)!=-1,"stat fail");
  check_error(S_ISDIR(fInfo.st_mode),"not a dir");
  
  check_error(nftw(argv[1],processFile,50,0)!=-1,"nftw fail");


exit(EXIT_SUCCESS);
}
     
