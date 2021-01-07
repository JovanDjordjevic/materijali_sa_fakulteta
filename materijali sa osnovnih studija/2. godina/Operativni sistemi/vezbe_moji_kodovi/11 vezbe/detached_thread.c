#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<errno.h>
#include<pthread.h>

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

void *threadFunc(void* arg){
    sleep(2);
    printf("detached thread provides the beans\n");

    return NULL;
}

int main(int argc,char **argv){
   
   pthread_t tid;
   check_thread(pthread_create(&tid,NULL,threadFunc,NULL),"create failed");
   
   check_thread(pthread_detach(tid),"detach failed");
   
   printf("main beans\n");
   
   sleep(4);
  
  exit(EXIT_SUCCESS);
}





