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
#include<sys/resource.h>
#include<stdint.h>

#define check_error(expr,userMsg)\
     do{\
       if(!(expr)){\
         fprintf(stderr,"%s\n",userMsg);\
         exit(EXIT_FAILURE);\
        }\
      }while(0);\
 
typedef struct{
  struct timeval Walltime;
  struct timeval Usertime;
  struct timeval Systime;
}stopwatch_t; 

void start(stopwatch_t *s){
   check_error(gettimeofday(&(s->Walltime),NULL)!=-1,"gettimeofday failed");
   
   struct rusage r;
   check_error(getrusage(RUSAGE_SELF,&r)!=-1,"getrusage fail");

   memcpy(&(s->Usertime),&(r.ru_utime),sizeof(struct timeval));
   memcpy(&(s->Systime),&(r.ru_stime),sizeof(struct timeval));  
}

int diff(stopwatch_t *a,stopwatch_t *b){
    intmax_t diff;  //racunamo dif U MIKROSEKUNDAMA i u upisujemo u struct b (tj u s jer smo nju prosledili kao b)
    diff=(a->Walltime.tv_sec*1000000-b->Walltime.tv_sec*1000000)+(a->Walltime.tv_usec-b->Walltime.tv_usec);  //walltime
    b->Walltime.tv_sec=diff/1000000;
    b->Walltime.tv_usec=diff%1000000;
    diff=(a->Usertime.tv_sec*1000000-b->Usertime.tv_sec*1000000)+(a->Usertime.tv_usec-b->Usertime.tv_usec);  //usertime
    b->Usertime.tv_sec=diff/1000000;
    b->Usertime.tv_usec=diff%1000000;
    diff=(a->Systime.tv_sec*1000000-b->Systime.tv_sec*1000000)+(a->Systime.tv_usec-b->Systime.tv_usec);  //systime
    b->Systime.tv_sec=diff/1000000;
    b->Systime.tv_usec=diff%1000000;        
}

void stop(stopwatch_t *s){
     stopwatch_t now;
     start(&now);
     diff(&now,s);
}



void print_time(stopwatch_t *s){
   printf("walltime sec:%d walltime usec: %d\n",(int)s->Walltime.tv_sec,(int)s->Walltime.tv_usec);
   printf("Usertime sec:%d Usertime usec: %d\n",(int)s->Usertime.tv_sec,(int)s->Usertime.tv_usec);
   printf("Systime sec:%d Systime usec: %d\n",(int)s->Systime.tv_sec,(int)s->Systime.tv_usec);      
}

      
int main(int argc,char **argv){
  
  stopwatch_t s;   
  start(&s);
 
     int i;             //neki primer nekog procesa
     int x,a,b,c;
     for(i=0;i<10000;i++){
       a=i;
       b=i/2;
       c=i%5;
       x=a*b+c-123456+9*17*2*3;
     }
  
  stop(&s);
  print_time(&s);
  
  exit(EXIT_SUCCESS);
}  



