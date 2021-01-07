#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<ftw.h>

#define check_error(expr,userMsg)\
       do{\
         if(!(expr)){\
           fprintf(stdout,"%s\n",userMsg);\
           exit(EXIT_FAILURE);\
         }\
       }while(0);
       
int reg=0;
int dir=0;
int chr=0;
int blk=0;
int lnk=0;
int fifo=0;
int sck=0;
int ukupno=0;       
       
int processFile(const char *path,const struct stat *sb,int typeflag,struct FTW *ftwbuf){
  
  switch(sb->st_mode & S_IFMT){
    case S_IFREG: reg++; ukupno++;break;
    case S_IFDIR: dir++; ukupno++;break;
    case S_IFCHR: chr++; ukupno++;break;
    case S_IFBLK: blk++; ukupno++;break;
    case S_IFLNK: lnk++; ukupno++;break;
    case S_IFIFO: fifo++; ukupno++;break;
    case S_IFSOCK: sck++; ukupno++; break;
    default: break;
  }
  
return 0;
}       
       
int main(int argc,char **argv){
 check_error(argc==2,"argumenti");
 struct stat fInfo;
  check_error(stat(argv[1],&fInfo)!=-1,"stat fail");
  check_error(S_ISDIR(fInfo.st_mode),"not dir");
  
check_error(nftw(argv[1],processFile,50,FTW_PHYS)!=-1,"nftw fail");

fprintf(stdout,"%d %d %d %d %d %d %d %d",reg,dir,chr,blk,lnk,fifo,sck,ukupno);

exit(EXIT_SUCCESS);
}





