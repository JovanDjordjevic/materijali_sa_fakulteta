//upotreba strftime

#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<errno.h>
#include<string.h>

#include<time.h>
#include<sys/time.h>

#define check_error(expr,userMsg)\
     do{\
       if(!(expr)){\
         fprintf(stderr,"%s\n",userMsg);\
         exit(EXIT_FAILURE);\
        }\
      }while(0);\
 
#define MAX_SIZE 1024     
      
int main(int argc,char **argv){

 time_t now=time(NULL);
 
 struct tm *brokenTime=localtime(&now);
   check_error((brokenTime!=NULL),"localtime failed");
   
 char buffer[MAX_SIZE];  
  
  int retVal=strftime(buffer,MAX_SIZE,"century:%C, Ymd:%F danas:%a",brokenTime);
   check_error(retVal!=0,"strftime failed");
   
   printf("%s\n",buffer);
  
  exit(EXIT_SUCCESS);
}  



