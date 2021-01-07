#include<stdio.h>
#include<stdlib.h>

#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<stdint.h>
#include<sys/wait.h>


#define check_error(expr,userMsg)\
         do{\
           if(!(expr)){\
            fprintf(stderr,"%s\n",userMsg);\
            exit(EXIT_FAILURE);\
            }\
           }while(0);
           
int main(int argc,char **argv){

pid_t childPid=fork();
check_error(childPid!=-1,"fork fail");

int x=10;
int y=15;

printf("pre forka: x=%d y=%d\n",x,y);

if(childPid>0){//parent

   x=x+5;
   y=y+10;
   printf("parent: x=%d y=%d\n",x,y);

}
else if(childPid==0){//child

   x=x+15;
   y=y-100;
   printf("child: x=%d y=%d\n",x,y);
   exit(EXIT_SUCCESS);
  
}
else //greska
 check_error(0,"else");
 
 check_error(wait(NULL)!=-1,"wait fail");
 
 printf("posle wait: x=%d y=%d\n",x,y);

  exit(EXIT_SUCCESS);
}

