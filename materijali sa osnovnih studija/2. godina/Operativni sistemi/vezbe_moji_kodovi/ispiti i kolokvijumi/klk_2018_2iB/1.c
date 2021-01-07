#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<math.h>

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
  check_error(stat(argv[1],&fInfo)!=-1,"stat");
  
  unsigned dif= (unsigned)( fabs(ceil((fInfo.st_atime-fInfo.st_mtime )/(3600.01))));
  
 fprintf(stdout,"%u\n",dif);
 
exit(EXIT_SUCCESS);
}













