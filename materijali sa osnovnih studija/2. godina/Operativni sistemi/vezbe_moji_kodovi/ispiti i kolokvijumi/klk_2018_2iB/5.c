#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

#include<ftw.h>
#include<string.h>

#define check_error(expr,userMsg)\
                  do{\
                  if(!(expr)){\
                   fprintf(stderr,"%s\n",userMsg);\
                   exit(EXIT_FAILURE);\
                   }\
                   }while(0);
char *ext=NULL;

int processFile(const char *path,const struct stat *sb,int typeflag,struct FTW *ftwbuf){
    if(typeflag==FTW_F){
       if((ftwbuf->level)>=2 && (ftwbuf->level)<=5){
           char *point=strrchr(path,'.');
           if(point!=NULL && !strcmp(point,ext)) {
             fprintf(stdout,"%s\n",path+ftwbuf->base);
           }
       
       }
   
   }
return 0;
}


int main(int argc,char* argv[]){
   check_error(argc==3,"argumenti");
 struct stat fInfo;
   check_error(stat(argv[1],&fInfo)!=-1,"stat");
   check_error(S_ISDIR(fInfo.st_mode),"niej dir");
 ext=argv[2];
 
 check_error(nftw(argv[1],processFile,50,0)!=-1,"nftw fail");

exit(EXIT_SUCCESS);
}













