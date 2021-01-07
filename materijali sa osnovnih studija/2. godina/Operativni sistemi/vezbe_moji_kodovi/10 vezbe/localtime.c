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
      
int main(int argc,char **argv){

  time_t now=time(NULL);  
  printf("%s",ctime(&now));   //upotreba ctime

 struct timeval tm;
 check_error(gettimeofday(&tm,NULL)!=-1,"gettiemofday failed"); //upotreba gettimeofday
 if(now==tm.tv_sec){
     printf("time==gettimeofday\n");
     printf("time dif=%d\n",(int)abs(now-tm.tv_sec));
 }
 else{
     printf("time!=gettimeofday\n");
     printf("time dif=%d\n",(int)abs(now-tm.tv_sec));
 }

 struct tm* brokenTime=localtime(&now);  //upotreba localtime
   check_error(brokenTime!=NULL,"localtime failed");

  printf("datum:%d.%d.%d\n",brokenTime->tm_mday,brokenTime->tm_mon+1,brokenTime->tm_year+1900);
  printf("vreme: %d:%d:%d\n",brokenTime->tm_hour,brokenTime->tm_min,brokenTime->tm_sec);

brokenTime->tm_year++;
time_t future=mktime(brokenTime); //upotreba mktime
  check_error(future!=-1,"mktime failed"); 
  printf("year in sec: %d\n",(int)(future-now));
  
  //ilustracija da mktime regulise ako povecamo previse
  brokenTime->tm_mday+=58;
  time_t novo=mktime(brokenTime);
    check_error(novo!=-1,"mktime failed");
  printf("%s\n",ctime(&novo));  

  exit(EXIT_SUCCESS);
}  



