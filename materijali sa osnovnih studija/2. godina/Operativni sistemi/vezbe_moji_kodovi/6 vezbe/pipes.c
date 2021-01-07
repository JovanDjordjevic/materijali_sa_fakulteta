#include<stdio.h>
#include<stdlib.h>

#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<stdint.h>
#include<sys/wait.h>
#include<string.h>

#define check_error(expr,userMsg)\
         do{\
           if(!(expr)){\
            fprintf(stderr,"%s\n",userMsg);\
            exit(EXIT_FAILURE);\
            }\
           }while(0);

#define WR_END (1)
#define RD_END (0)
#define MAX_SIZE 256
           
int main(int argc,char **argv){

int par2cld[2];
  check_error(pipe(par2cld)!=-1,"pipe1");
int cld2par[2];
  check_error(pipe(cld2par)!=-1,"pipe2");
  
  
pid_t pid=fork();
  check_error(pid!=-1,"fork");
  
if(pid>0){//parent
   close(par2cld[RD_END]);
   close(cld2par[WR_END]);
   
   char *line=NULL;         //pisanje poruke za child
   size_t len=0;
   
   check_error(getline(&line,&len,stdin)!=-1,"parent getline fail");
   check_error(len<256,"too long");   
   check_error(write(par2cld[WR_END],line,len)!=-1,"parent write fail");

   char buffer[MAX_SIZE];    //citanje odgovora od childa
   int bytesRead;
   check_error((bytesRead=read(cld2par[RD_END],buffer,MAX_SIZE))!=-1,"parent read fail");
   
   check_error(write(STDOUT_FILENO,buffer,bytesRead)!=-1,"parent stdout write fail");
   
   free(line);
   close(par2cld[WR_END]);
   close(cld2par[RD_END]);
   
}
else if(pid==0){//child
   close(par2cld[WR_END]);
   close(cld2par[RD_END]); 
   
   char buffer[MAX_SIZE];//cekanje poruke od parenta i ispisivanje na stdout
   int bytesRead;
   memset(buffer,0,MAX_SIZE);
   strcpy(buffer,"CHILD: ");
   check_error(write(STDOUT_FILENO,buffer,strlen(buffer))!=-1,"fail")
    check_error((bytesRead=read(par2cld[RD_END],buffer,MAX_SIZE))!=-1,"child read fail");
   check_error(write(STDOUT_FILENO,buffer,bytesRead)!=-1,"child write fail");
   
   char *s="success\n"; //slanje odgovora parentu
   check_error(write(cld2par[WR_END],s,sizeof(s))!=-1,"cld2par write fail");
   
   close(par2cld[RD_END]);
   close(cld2par[WR_END]);
   
exit(EXIT_SUCCESS);
}

else{
  check_error(0,"else");
}
  check_error(wait(NULL)!=-1,"wait fail");
  
  exit(EXIT_SUCCESS);
}

