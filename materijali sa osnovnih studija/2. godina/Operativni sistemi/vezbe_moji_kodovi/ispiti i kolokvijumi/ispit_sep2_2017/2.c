//zakljucava i brojeve na kojima vec postoji read lock a ne treba to da radi


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
     
     FILE *in=fdopen(fd,"r+");
       check_error(in!=NULL,"fopen");
     char rec[256];
     
     while(fscanf(in,"%s",rec)==1){
        
        long int x=strtol(rec,NULL,10);
          if(x>=1000 && x<=9999){
             
             struct flock lock;
               lock.l_type=F_RDLCK;
               lock.l_whence=SEEK_SET;
               lock.l_start=ftell(in);
               lock.l_len=-4;
               
               int ret=fcntl(fd,F_GETLK,&lock);
                 if(ret==-1){
                    if(errno==EACCES) printf("aces\n");
                    else if(errno==EAGAIN) printf("aagain\n");
                    else check_error(0,"else getlk");                    
                 }
               
               
               if(lock.l_type==F_UNLCK){
                   
               lock.l_type=F_RDLCK;
               lock.l_whence=SEEK_SET;
               lock.l_start=ftell(in);
               lock.l_len=-4;
               
               check_error(fcntl(fd,F_SETLK,&lock)!=-1,"setlock");
                   
                   check_error(fseek(in,-4,SEEK_CUR)!=-1,"fseek");
                   fprintf(in,"####");
                     
                }
                  
          }
      }
     
        
        
     fclose(in);
  exit(EXIT_SUCCESS);
}
