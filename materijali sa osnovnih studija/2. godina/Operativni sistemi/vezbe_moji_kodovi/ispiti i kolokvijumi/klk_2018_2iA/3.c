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
  check_error(argc==2,"argumenti");
 struct stat fInfo;
  check_error(stat(argv[1],&fInfo)!=-1,"stat fail");
 
 unsigned group=0;
 unsigned others=0;
 unsigned user=0;
 
 if((fInfo.st_mode & S_IRUSR)!=0){ user=user | S_IRUSR;}
 if((fInfo.st_mode & S_IWUSR)!=0){ user=user | S_IWUSR;}
 if((fInfo.st_mode & S_IXUSR)!=0){ user=user | S_IXUSR;}
 
 if((fInfo.st_mode & S_IRGRP)!=0){ others=others | S_IROTH;}
 if((fInfo.st_mode & S_IWGRP)!=0){ others=others | S_IWOTH;}
 if((fInfo.st_mode & S_IXGRP)!=0){ others=others | S_IXOTH;}
  
 if((fInfo.st_mode & S_IROTH)!=0){ group=group | S_IRGRP;}
 if((fInfo.st_mode & S_IWOTH)!=0){ group=group | S_IWGRP;}
 if((fInfo.st_mode & S_IXOTH)!=0){ group=group | S_IXGRP;}
 
 unsigned privileges=0;
  privileges= privileges | user;
  privileges= privileges | group;
  privileges= privileges | others;
      
check_error(chmod(argv[1],privileges)!=-1,"chmod fail");      
      

exit(EXIT_SUCCESS);
}













