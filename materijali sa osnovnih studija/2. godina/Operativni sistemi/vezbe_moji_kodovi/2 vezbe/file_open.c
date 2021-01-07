#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#define check_error(expr,userMsg)\
                  do{\
                  if(!(expr)){\
                   fprintf(stderr,"%s\n",userMsg);\
                   exit(EXIT_FAILURE);\
                   }\
                   }while(0);


int myopen(const char *pathname,const char *mode){
   mode_t privileges=0644;
   int flags=0;
   
   switch(mode[0]){
     case 'r':  if(mode[1]=='+')  {flags=flags | O_RDWR; } 
                else flags=flags | O_RDONLY;
                break; 
     case 'w': if(mode[1]=='+') {flags=flags | O_RDWR;}
                else {flags=flags | O_WRONLY;}
               flags=flags | O_CREAT;
               flags=flags | O_TRUNC;
               break;
     case 'a': if(mode[1]=='+') {flags=flags | O_RDWR;}
                else {flags=flags | O_WRONLY;}
               flags=flags | O_CREAT;
               flags=flags | O_APPEND;
               break;  
     default: return -1; break;
   }
   int fd=open(pathname,flags,privileges);
   return fd;
}


// a.out file mode
int main(int argc,char* argv[]){
 check_error((3==argc),"argumenti");
 
 int fd=myopen(argv[1],argv[2]);
    check_error((fd!=-1),"open fail");
 
 close(fd);

exit(EXIT_SUCCESS);
}













