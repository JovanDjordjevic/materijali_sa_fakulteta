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
#define MAX_SIZE (63)


                  
int main(int argc, char **argv){
    
    check_error(argc==2,"args");
    
    time_t x=atoi(argv[1]);
    
    struct tm *brokenTime=localtime(&x);
     
     switch(brokenTime->tm_wday){
        case 0: printf("nedelja\n"); break;
        case 1: printf("ponedeljak\n"); break;
        case 2: printf("utorak\n"); break;
        case 3: printf("sreda\n"); break;
        case 4: printf("cetvrtak\n"); break;
        case 5: printf("petak\n"); break;
        case 6: printf("subota\n"); break;
        default: break;
     }
     
     
  exit(EXIT_SUCCESS);
}
