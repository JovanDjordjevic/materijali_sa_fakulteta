//20%

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
#include<signal.h>
#include<ctype.h>
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
#define RD_END (0)
#define WR_END (1)
#define ARRAY_MAX (1024)
               
int main(int argc, char **argv){

   check_error(argc==2,"args");
   
   int fd=open(argv[1],O_RDWR);
     check_error(fd!=-1,"open");
   FILE *in=fdopen(fd,"r+");
     check_error(in!=NULL,"fdopen");  
   
   struct flock lock;
   char rec[256];
   int count=0;
   
   while(fscanf(in,"%s",rec)==1){
      
      char *end;
      long int x=strtol(rec,&end,10);
      
      if(end==NULL || *end=='\0'){//jeste broj
         
         lock.l_type=F_RDLCK;
         lock.l_whence=SEEK_SET;
         lock.l_start=ftell(in);
         lock.l_len=-strlen(rec);
         
         int retVal=fcntl(fd,F_SETLK,&lock);
         if(retVal!=-1) count++;
         else if(errno!=EAGAIN && errno!=EACCES){
            check_error(0,"fcntl");
         }
      }
      
   }  
   
    fclose(in);  
  exit(EXIT_SUCCESS);
}
