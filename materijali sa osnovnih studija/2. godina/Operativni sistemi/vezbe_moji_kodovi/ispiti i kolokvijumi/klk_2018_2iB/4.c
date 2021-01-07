#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

#define MAX_SIZE 1024
#define check_error(expr,userMsg)\
                  do{\
                  if(!(expr)){\
                   fprintf(stderr,"%s\n",userMsg);\
                   exit(EXIT_FAILURE);\
                   }\
                   }while(0);


int main(int argc,char* argv[]){
  check_error(argc==4,"argumenti");
  
  off_t offset=atoi(argv[2]); //a
  int duzina=atoi(argv[3]); //b

/*struct stat fInfo;
 check_error(stat(argv[1],&fInfo)!=-1,"stat fail");
*/
int fd=open(argv[1],O_RDWR);
 check_error(fd!=-1,"open fail");
 
 check_error(lseek(fd,offset,SEEK_SET)!=-1,"lseek fail");

 int readBytes=0;
 int bytesWritten=0;
 char *buffer=malloc(MAX_SIZE);
   check_error(buffer!=NULL,"alokacija");
 
 while( (readBytes=read(fd,buffer,MAX_SIZE))>0 && bytesWritten!=duzina){
     
     if(duzina==readBytes){
        if( (write(STDOUT_FILENO,buffer,readBytes))<0 ){
           free(buffer);
           check_error(0,"write1");
        }
     }
     else if(duzina<readBytes){
        if( (write(STDOUT_FILENO,buffer,duzina))<0 ){
           free(buffer);
           check_error(0,"write2");
        }
     }
     else if(duzina>readBytes){
            bytesWritten+=readBytes;
        if( (write(STDOUT_FILENO,buffer,readBytes))<0 ){
           free(buffer);
           check_error(0,"write3");
        }
     }
     else {check_error(0,"else");}
       
 }


exit(EXIT_SUCCESS);
}













