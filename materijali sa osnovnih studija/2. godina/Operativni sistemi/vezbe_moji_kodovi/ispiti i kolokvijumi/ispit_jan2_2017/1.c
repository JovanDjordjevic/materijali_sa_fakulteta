#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<sys/wait.h>
#include<time.h>
#include<errno.h>
#include<string.h>

#define check_error(expr,userMsg)\
             do{\
               if(!(expr)){\
                 fprintf(stderr,"%s\n",userMsg);\
                 exit(EXIT_FAILURE);\
                }\
              }while(0);

int main(int argc,char **argv){
      
      check_error(argc==2,"args");
    time_t now=time(NULL);
    
    time_t new=now+(atoi(argv[1]))*24*60*60;
    
    struct tm *brokenTime=localtime(&new); 
      check_error(brokenTime!=NULL,"localtime");
     
     char dan[15];
      
    switch(brokenTime->tm_wday){
       case 0: strcpy(dan,"nedelja"); break;
       case 1: strcpy(dan,"ponedeljak"); break;
       case 2: strcpy(dan,"utorak"); break;
       case 3: strcpy(dan,"sreda"); break;
       case 4: strcpy(dan,"cetvrtak"); break;
       case 5: strcpy(dan,"petak"); break;
       case 6: strcpy(dan,"subota"); break;    
    }
    
    printf("%s %d\n",dan,brokenTime->tm_mday);
      
      
    
  
    exit(EXIT_SUCCESS);
}





