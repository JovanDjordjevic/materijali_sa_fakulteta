#include<stdio.h>
#include<stdlib.h>

#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

#include<string.h>

#define check_error(expr,userMsg)\
                  do{\
                  if(!(expr)){\
                   fprintf(stderr,"%s\n",userMsg);\
                   exit(EXIT_FAILURE);\
                   }\
                   }while(0);


int main(int argc,char* argv[]){
  check_error(argc==3,"argumenti");
  
 if(!strcmp("-f",argv[1])){
    if(unlink(argv[2])==-1){
      printf("unlink -f\n");
      exit(EXIT_FAILURE);
    }
 }
 else if(!strcmp("-d",argv[1])){
 
   if(rmdir(argv[2])==-1){  //rmdir brise SAMO prazne
      printf("unlink -d\n");
      exit(EXIT_FAILURE);   
     }
  }    
 else{
 printf("niej naveden -f ili -d\n");
    exit(EXIT_FAILURE);   
 }
 
exit(EXIT_SUCCESS);
}













