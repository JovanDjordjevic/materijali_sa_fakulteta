#define _GNU_SOURCE
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
#define MAX_SIZE (64)

int s1c=0;
int s2c=0;
int st=0;

void sigHandler(int signum){
   
   switch(signum){
     case SIGUSR1: s1c++; break;
     case SIGUSR2: s2c++; break;
     case SIGTERM: st++; break;
     default: break;
   }

}

                  
int main(int argc, char **argv){
    
    check_error(argc==1,"args");
    
    //printf("pid:%d\n",(int)getpid());
    char rec[MAX_SIZE];
        
    
    while(1){
      
       check_error(signal(SIGUSR1,sigHandler)!=SIG_ERR,"signal1");
       check_error(signal(SIGUSR2,sigHandler)!=SIG_ERR,"signal2");       
       check_error(signal(SIGTERM,sigHandler)!=SIG_ERR,"signal3");
      
    
       
      pause(); //!! ovo je failo i zato nije radilo
     scanf("%s",rec);
      //pause(); moze i ovde
        
      if(s1c){
         int len=strlen(rec);
         int i;
           for(i=0;i<len/2;i++){
                char temp;
                temp=rec[i];
                rec[i]=rec[len-i-1];
                rec[len-i-1]=temp;
                }
            printf("%s\n",rec);
         s1c=0;
      }
      
    
       if(s2c){
        int len=strlen(rec);
        int i;
        for(i=0;i<len;i++){
         if(islower(rec[i])) rec[i]=toupper(rec[i]);   
        }
        printf("%s\n",rec);
        s2c=0;
      }
      
      
       if(st){
         exit(EXIT_SUCCESS);
      }
    
    
    }
 
  exit(EXIT_SUCCESS);
}
