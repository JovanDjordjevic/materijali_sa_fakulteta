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



int main(int argc,char **argv){
  check_error(argc==2,"argumenti");
  struct stat fInfo;
  check_error(stat(argv[1],&fInfo)!=-1,"stat fail");
  
 char s[11];
 strcpy(s,"-rwxrwxrwx");
 switch(fInfo.st_mode & S_IFMT){
   case S_IFREG: s[0]='-'; break;
   case S_IFDIR: s[0]='d'; break;
   case S_IFCHR: s[0]='c'; break;
   case S_IFBLK: s[0]='b'; break;
   case S_IFIFO: s[0]='f'; break;
   case S_IFLNK: s[0]='l'; break;
   case S_IFSOCK: s[0]='s'; break;
 default: break;
 }

if( !(fInfo.st_mode & S_IRUSR) ) s[1]='-';
if( !(fInfo.st_mode & S_IWUSR) ) s[2]='-';
if( !(fInfo.st_mode & S_IXUSR) ) s[3]='-';
if( !(fInfo.st_mode & S_IRGRP) ) s[4]='-';
if( !(fInfo.st_mode & S_IWGRP) ) s[5]='-';
if( !(fInfo.st_mode & S_IXGRP) ) s[6]='-';
if( !(fInfo.st_mode & S_IROTH) ) s[7]='-';
if( !(fInfo.st_mode & S_IWOTH) ) s[8]='-';
if( !(fInfo.st_mode & S_IXOTH) ) s[9]='-';


fprintf(stdout,"%s\n",s);
exit(EXIT_SUCCESS);
}








