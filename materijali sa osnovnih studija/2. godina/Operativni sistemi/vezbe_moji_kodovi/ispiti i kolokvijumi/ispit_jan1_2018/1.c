#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

#include<errno.h>
#include<time.h>
#include<string.h>

#define check_error(expr,userMsg)\
                do{\
                  if(!(expr)){\
                    fprintf(stderr,"%s\n",userMsg);\
                    exit(EXIT_FAILURE);\
                   }\
                 }while(0);

int main(int argc, char **argv){

  check_error(argc==2,"args");
  
  time_t sec=atoi(argv[1]);
  
  struct tm* brokenTime=localtime(&sec);
  
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
    default: break;
  }

  exit(EXIT_SUCCESS);
}
                 
