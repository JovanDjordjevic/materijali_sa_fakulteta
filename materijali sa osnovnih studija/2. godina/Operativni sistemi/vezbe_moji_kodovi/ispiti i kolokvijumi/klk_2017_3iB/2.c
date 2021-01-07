#define _XOPEN_SOURCE 700

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<math.h>


#define check_error(expr,usrMsg)\
            do{\
              if(!(expr)){\
                fprintf(stderr,"%s\n",usrMsg);\
                exit(EXIT_FAILURE);\
              }\
            }while(0);


int main(int argc,char **argv){
     check_error(argc==3,"argumenti");
   struct stat fInfo;
     check_error(stat(argv[1],&fInfo)!=-1,"stat");
  
  unsigned size;
  
  if( strchr(argv[1],'/')!=NULL ){
      char *ime=strrchr(argv[1],'/')+1;
      if(!strcmp(argv[2],"KB")){
          size=(unsigned)((fInfo.st_size)/1024)+1; 
          fprintf(stdout,"%s %uKB",ime,size);
        }
      else if(!strcmp(argv[2],"MB")){
          size=(unsigned)((fInfo.st_size)/(1024*1024))+1; 
          fprintf(stdout,"%s %uMB",ime,size);
        }
      else if(!strcmp(argv[2],"GB")){
          size=(unsigned)((fInfo.st_size)/(1024*1024*1024))+1; 
          fprintf(stdout,"%s %uGB",ime,size);
        }
      else {check_error(0,"else 2");}  
  }
  else{
      if(!strcmp(argv[2],"KB")){
          size=(unsigned)((fInfo.st_size)/1024)+1; 
          fprintf(stdout,"%s %uKB",argv[1],size);
        }
      else if(!strcmp(argv[2],"MB")){
          size=(unsigned)((fInfo.st_size)/(1024*1024))+1; 
          fprintf(stdout,"%s %uMB",argv[1],size);
        }
      else if(!strcmp(argv[2],"GB")){
          size=(unsigned)((fInfo.st_size)/(1024*1024*1024))+1; 
          fprintf(stdout,"%s %uGB",argv[1],size);
        }
      else {check_error(0,"else 2");}     
  }  
  
 exit(EXIT_SUCCESS);
}
