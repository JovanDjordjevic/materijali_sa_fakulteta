#define _XOPEN_SOURCE 700     
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

#include<string.h>
#include<errno.h>
#include<sys/wait.h>

#define check_error(expr,userMsg)\
           do{\
             if(!(expr)){\
               fprintf(stderr,"%s\n",userMsg);\
               exit(EXIT_FAILURE);\
             }\
           }while(0);


            
int main(int argc,char **argv){

check_error(argc==6,"argumenti");

char *path=argv[1];
int start=atoi(argv[2]);
int len=atoi(argv[3]);   //u bajtovima
int sleepTime=atoi(argv[4]); //u sekundama
int lockType=argv[5][0]=='r' ? F_RDLCK : F_WRLCK;

int fd=open(path,O_RDWR);
  check_error(fd!=-1,"open fail");
  
 struct flock lock;
    lock.l_type=lockType;
    lock.l_whence=SEEK_SET;
    lock.l_start=start;
    lock.l_len=len; //ako je len 0, zakljucava se sve od starta do kraja fajla
    
 printf("zakljucavanje..."); 
 check_error(fcntl(fd,F_SETLK,&lock)!=-1,"fcntl failed");
 printf("uspesno\n");
 
 sleep(sleepTime); 
 
 lock.l_type=F_UNLCK;
 printf("Otkljucavanje...");
 check_error(fcntl(fd,F_SETLK,&lock)!=-1,"fcntl fail");
 printf("uspesno\n");   
    
 close(fd);   

 exit(EXIT_SUCCESS);
}



















