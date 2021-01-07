#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<sys/wait.h>
#include<pthread.h>
#include<errno.h>

#define check_error(expr,userMsg)\
             do{\
               if(!(expr)){\
                 fprintf(stderr,"%s\n",userMsg);\
                 exit(EXIT_FAILURE);\
                }\
              }while(0);


int main(int argc,char **argv){
     check_error(argc==4,"argumenit");
     
     int a=atoi(argv[2]);  //udaljenje
     int b=atoi(argv[3]);  //br bajtova
     
     int fd=open(argv[1],O_RDWR);
       check_error(fd!=-1,"open");
     
     struct flock lock;
      lock.l_type=F_WRLCK;
      lock.l_whence=SEEK_SET;
      lock.l_start=a;
      lock.l_len=b;
     
     check_error(fcntl(fd,F_GETLK,&lock)!=-1,"fcntl1");
        //GETLK vraca u lock.l_type lock koji trenutno psotoji na tom mestu
     switch(lock.l_type){
      
        case F_UNLCK: printf("unlocked\n"); break;
        case F_RDLCK: printf("shared lock\n"); break;
        case F_WRLCK: printf("exclusive lock\n"); break;
     
     }
     
     
  exit(EXIT_SUCCESS);
}





