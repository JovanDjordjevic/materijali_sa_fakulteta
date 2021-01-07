#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>


#define check_error(expr,userMsg)\
                  do{\
                  if(!expr){\
                   fprintf(stderr,"%s\n",userMsg);\
                   exit(EXIT_FAILURE);\
                   }\
                   }while(0);

int myopen(const char *path, const char *mode){
int flags=0;
mode_t privileges=0644;
 switch(mode[0]){
 case 'r': flags |= (mode[1]=='+')? O_RDWR : O_RDONLY; 
           break;
 case 'w': flags |= (mode[1]=='+')? O_RDWR : O_WRONLY;
           flags |= O_CREAT;
           flags |= O_TRUNC;   
           break;
 case 'a': flags |= (mode[1]=='+')? O_RDWR : O_WRONLY;
           flags |= O_CREAT;
           flags |= O_APPEND;   
           break;
 default: return -1; 
  }
int fd=open(path,flags,privileges);
return fd;
}

void kopiranje_na_terminal(int fd){
unsigned int memBuffSize = 1<<13; //2^13=8*2^10 -> 8KB,definisemo velicinu bafera

char *buffer=malloc(memBuffSize);
 check_error((buffer!=NULL),"alokacija");

int readBytes;  //broj procitanih bajtova
 while((readBytes=read(fd,buffer,memBuffSize))>0){
   if((write(STDOUT_FILENO,buffer,readBytes))<0) {
     free(buffer);
     fprintf(stdout,"pisanje\n");
     exit(EXIT_FAILURE);
   }
 }
free(buffer);
}



int main(int argc,char* argv[]){
  
  check_error((argc==3),"argumenti");
  int fd=myopen(argv[1],argv[2]);
  check_error((fd!=-1),"open fail");
  
  kopiranje_na_terminal(fd);
  close(fd);

exit(EXIT_SUCCESS);
}













