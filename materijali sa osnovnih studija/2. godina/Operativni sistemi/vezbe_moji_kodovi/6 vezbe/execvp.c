#include<stdio.h>
#include<stdlib.h>

#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<sys/wait.h>
#include<string.h>

#define check_error(expr,userMsg)\
         do{\
           if(!(expr)){\
            fprintf(stderr,"%s\n",userMsg);\
            exit(EXIT_FAILURE);\
            }\
           }while(0);


int main(int argc,char **argv){
  
  check_error(argc>1,"argumenti");
  
  char **program=NULL;
  program=malloc((argc+1)*sizeof(char*));
    check_error(program!=NULL,"aloakcija");
  
  program[0]=malloc(strlen(argv[1])+1);
    check_error(program[0]!=NULL,"aloakcija prvog argumenta");
  strcpy(program[0],argv[1]);
  
  char *ptr=strrchr(argv[1],'/');
      ptr= (ptr!=NULL) ?  ptr+1 : argv[1];
  
      program[1]=malloc(strlen(ptr)+1);
         check_error(program[1]!=NULL,"alokacija drugog argumenta");
         strcpy(program[1],ptr+1);
      
      int i;
      for( i=2; i<argc; i++){
        program[i]=malloc(strlen(argv[i]+1));
          check_error(program[i]!=NULL,"alokacija i-tog");
        strcpy(program[i],argv[i]);      
      } 
     
      program[argc]=NULL;
   
      pid_t pid=fork();
      
      if(pid==0){//child
       
          check_error(execvp(program[0],program+1)!=-1,"execvp fail");
          
       exit(EXIT_SUCCESS);
      }   
        
     int status=0;
     check_error(waitpid(pid,&status,0)!=-1,"waitpid");
     
     if(WIFEXITED(status)){
         if(WEXITSTATUS(status)==EXIT_SUCCESS){
             printf("pokretanje uspesno\n");
           }
         else{
             printf("pokretanje neuspesno\n");
           }
     } 
   
     for(i=0;i<argc+1;i++){
       free(program[i]);
     }
     
     free(program);

  exit(EXIT_SUCCESS);
}





















