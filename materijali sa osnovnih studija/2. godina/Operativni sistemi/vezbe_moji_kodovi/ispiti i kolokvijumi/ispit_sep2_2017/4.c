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

                  
int main(int argc, char **argv){
    
    check_error(argc==2,"args");
    
    time_t sec=atoi(argv[1]);
    
    struct tm *brokenTime=localtime(&sec); 
    
    switch(brokenTime->tm_mon){
       case 0: printf("januar\n"); break;
       case 1: printf("februar\n"); break;
       case 2: printf("mart\n"); break;
       case 3: printf("april\n"); break;
       case 4: printf("maj\n"); break;
       case 5: printf("jun\n"); break;
       case 6: printf("jul\n"); break;
       case 7: printf("avgust\n"); break;
       case 8: printf("septembar\n"); break;
       case 9: printf("oktobar\n"); break;
       case 10: printf("novembar\n"); break;
       case 11: printf("decembar\n"); break;
    }
 
  exit(EXIT_SUCCESS);
}
