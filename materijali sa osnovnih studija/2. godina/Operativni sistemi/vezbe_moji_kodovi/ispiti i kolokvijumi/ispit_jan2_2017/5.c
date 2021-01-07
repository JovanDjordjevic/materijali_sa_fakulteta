#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<sys/wait.h>
#include<pthread.h>
#include<errno.h>
#include<string.h>
#include<semaphore.h>
#include<sys/mman.h>

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
#define MAX_STR_LEN 256



            
int main(int argc,char **argv){
       
       check_error(argc==3,"args");
       
       int fd=open(argv[1],O_RDWR);
         check_error(fd!=-1,"open");
       
       FILE *in=fdopen(fd,"r+");
         check_error(in!=NULL,"fopen"); 
       
       char rec[1024];
       int wLen=strlen(argv[2]);
       
       while(fscanf(in,"%s",rec)==1){
         
         if(!strcmp(rec,argv[2])){
               
               struct flock lock;
                 lock.l_type=F_WRLCK;
                 lock.l_whence=SEEK_SET;      
                 lock.l_start=ftell(in);
                 lock.l_len=-wLen;
                 
                 check_error(fcntl(fd,F_GETLK,&lock)!=-1,"lock failed");
                 long offset=ftell(in)-wLen;
                 
                 switch(lock.l_type){
                    case F_UNLCK: break;
                    case F_WRLCK: printf("%ld w\n",offset); break;
                    case F_RDLCK: printf("%ld r\n",offset); break;
                    default: break;
                 }
          }
       
             
       }
      
      
      fclose(in);
    exit(EXIT_SUCCESS);
}





