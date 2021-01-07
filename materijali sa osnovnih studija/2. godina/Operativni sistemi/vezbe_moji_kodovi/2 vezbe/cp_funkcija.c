#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>


#define check_error(expr,userMsg)\
                  do{\
                  if(!expr){\
                   fprintf(stderr,"%s\n",userMsg);\
                   exit(EXIT_FAILURE);\
                   }\
                   }while(0);


void kopiraj (int fdSrc,int fdDest){

 unsigned int buffSize = 1<<13; //8KB
 char *buffer=malloc(buffSize);
 check_error((buffer!=NULL),"alokacija")
 
 int readBytes=0;
 while( (readBytes=read(fdSrc,buffer,buffSize))>0 ){
    
     if((write(fdDest,buffer,readBytes))<0){
      free(buffer);
      fprintf(stderr,"write\n");
      exit(EXIT_FAILURE);
     }
 }
 check_error((readBytes!=-1),"read");
 
free(buffer);
}




int main(int argc,char* argv[]){
  
  check_error((argc==3),"argumenti");
  
  int fdSrc=open(argv[1],O_RDONLY);
   check_error((fdSrc!=-1),"open Src fail");
  int fdDest=open(argv[2],O_WRONLY|O_TRUNC|O_CREAT,0644);
   check_error((fdDest!=-1),"open Dest fail");
   
 kopiraj(fdSrc,fdDest);
 
 close(fdSrc);  
 close(fdDest);  
   
exit(EXIT_SUCCESS);
}













