#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#include<errno.h>
#include<pthread.h>
#include<string.h>
#include<sys/wait.h>

#define check_error(expr,userMsg)\
                do{\
                  if(!(expr)){\
                     fprintf(stderr,"%s\n",userMsg);\
                     exit(EXIT_FAILURE);\
                    }\
                  }while(0);
                  
#define check_thread(err,userMsg)\
                do{\
                  int _err=err;\
                  if(_err){\
                    errno=_err;\
                    check_error(0,userMsg);\
                   }\
                  }while(0);
#define RD_END (0)
#define WR_END (1)
#define MAX_SIZE (256)
                  
int main(int argc, char **argv){
     
     check_error(argc==2,"args");
     
     int fd=open(argv[1],O_RDWR);
       check_error(fd!=-1,"open");
     
       
      struct flock lock;
        lock.l_type=F_RDLCK;
        lock.l_whence=SEEK_SET;
        lock.l_start=8;
        lock.l_len=5;
       
       int retval=fcntl(fd,F_SETLK,&lock);
       
       lock.l_type=F_WRLCK;
        lock.l_whence=SEEK_SET;
        lock.l_start=16;
        lock.l_len=4;
       
       retval=fcntl(fd,F_SETLK,&lock);
       
       sleep(20); 
        
     close(fd);
  exit(EXIT_SUCCESS);
}
