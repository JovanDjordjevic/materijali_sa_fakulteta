#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

#include<errno.h>

#define MAXSIZE 1024
#define check_error(expr,userMsg)\
                  do{\
                  if(!(expr)){\
                   fprintf(stderr,"%s\n",userMsg);\
                   exit(EXIT_FAILURE);\
                   }\
                   }while(0);




int main(int argc,char* argv[]){

check_error(argc==3,"argumenti");

long privileges=strtol(argv[2],NULL,8); //NULL jer nas ne interesuje na kom mestu je greska, 8 jer je arg dat oktalno

 mode_t oldUmask=umask(0);
  int fd=open(argv[1],O_CREAT|O_RDWR|O_EXCL,privileges); //O_EXCL omogucava da se fajl napravi akko vec ne psotoji
  
  if(fd==-1){
     if(errno==EEXIST){
       printf("fajl vec psotoji\n");
       check_error(chmod(argv[1],privileges)!=-1,"chmod fail"); //ako vec psotoji, promenimo mu prava pristupa pomocu chmod
     }
     else {
      printf("open fail\n");
      exit(EXIT_FAILURE);
     }
     
  }else
  {close(fd);}
  
  
 umask(oldUmask); 
exit(EXIT_SUCCESS);
}

