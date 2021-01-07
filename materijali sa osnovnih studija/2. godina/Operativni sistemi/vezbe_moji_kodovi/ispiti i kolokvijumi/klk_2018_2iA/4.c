#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

#define MAX_SIZE 1024
#define check_error(expr,userMsg)\
                  do{\
                  if(!(expr)){\
                   fprintf(stderr,"%s\n",userMsg);\
                   exit(EXIT_FAILURE);\
                   }\
                   }while(0);


int main(int argc,char* argv[]){
  
  FILE *in=fopen(argv[1],"r");
    check_error(in!=NULL,"fopen");
  
  int fdDest=open(argv[2],O_RDWR);
   check_error(fdDest!=-1,"open2 fail");   
 
 int offset;
 char rec[MAX_SIZE];
 
 while(fscanf(in,"%d %s",&offset,rec)==2){
    
    check_error(lseek(fdDest,offset,SEEK_SET)!=-1,"lseek");
    if(write(fdDest,rec,strlen(rec))<0){
      check_error(0,"write");
    }
 
 }
 
 
 fclose(in);
 close(fdDest);
exit(EXIT_SUCCESS);
}













