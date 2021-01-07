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
#include<string.h>
#include<ctype.h>

#define check_error(expr,userMsg)\
             do{\
               if(!(expr)){\
                 fprintf(stderr,"%s\n",userMsg);\
                 exit(EXIT_FAILURE);\
                }\
              }while(0);
#define check_thread(err,userMsg)\
          do{\
            int _err=err;\
            if(_err){\
              errno=_err;\
              check_error(0,userMsg);\
             }\
            }while(0);

#define RD_END (0)
#define WR_END (1)

void opl(char *rec){
   int i,len=strlen(rec);
   for(i=0;i<len;i++){
     if(isupper(rec[i])) rec[i]=tolower(rec[i]);
   }
}
void opu(char *rec){
  int i,len=strlen(rec);
   for(i=0;i<len;i++){
     if(islower(rec[i])) rec[i]=toupper(rec[i]);
   }
}
void opr(char *rec){
  int i,str=strlen(rec);
  int len=str/2;
  
  for(i=0;i<len;i++){
  
    char temp=rec[i];
    rec[i]=rec[str-i-1];
    rec[str-i-1]=temp;
  }   
}
            
int main(int argc,char **argv){
    
  
    char rec[63];
    char c;    
 
    while((scanf("%s %c",rec,&c))==2){
    
         if(c!='l' && c!='r' && c!='u') { check_error(0,"komanda"); }
      int cld2par[2];
        check_error(pipe(cld2par)!=-1,"pipe failed");
      
      pid_t pid=fork();
        check_error(pid!=-1,"fork");

      if(pid==0){//child 
        
        close(cld2par[RD_END]);
      
          if(c=='l'){
             opl(rec);
          }
          else if(c=='u'){
             opu(rec);
          }
          else if(c=='r'){
             opr(rec);
          }
        check_error(write(cld2par[WR_END],rec,63)!=-1,"write failed"); 
                   
        close(cld2par[WR_END]);
        exit(EXIT_SUCCESS);  
      } 
      
      //parent
       close(cld2par[WR_END]);
      
      FILE *in=fdopen(cld2par[RD_END],"r");
        check_error(in!=NULL,"fdopen");
      char nova[63];
      fscanf(in,"%s",nova);
      printf("%s\n",nova);
      
      close(cld2par[RD_END]);
      fclose(in);
      
      
     check_error(wait(NULL)!=-1,"wait");
    }
    
      
    exit(EXIT_SUCCESS);
}





