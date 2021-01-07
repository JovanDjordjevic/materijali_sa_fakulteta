#define _XOPEN_SOURCE 700
 
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>
#include<dirent.h>

#define check_error(expr,usrMsg)\
           do{\
             if(!(expr)){\
                fprintf(stderr,"%s\n",usrMsg);\
                exit(EXIT_FAILURE);\
              }\
            }while(0); 
            
bool traverse(const char *path,off_t *max, off_t *min){

  struct stat fInfo;
   if(lstat(path,&fInfo)==-1 )return false;
   
  if(S_ISREG(fInfo.st_mode)){ 
   if(fInfo.st_size<(*min)) { (*min)=fInfo.st_size;}
   if(fInfo.st_size>(*max)) { (*max)=fInfo.st_size;}
  }
  if(!S_ISDIR(fInfo.st_mode)) return true;
  
  DIR *dir=opendir(path);
  if(dir==NULL) return false;
  if(chdir(path)==-1) return false;
  
  struct dirent *current;
  while( (current=readdir(dir))!=NULL ){
      if(!strcmp(current->d_name,".") || !strcmp(current->d_name,"..")) continue;
      
      bool status=traverse(current->d_name,max,min);
      if(status==false) return false;
  }
  if(chdir("..")==-1) return false;
  if(closedir(dir)==-1) return false;

return true;
}            
            
int main(int argc,char **argv){
    check_error(argc==2,"argumenti");
  struct stat fInfo;
   check_error(lstat(argv[1],&fInfo)!=-1,"stat fail");
   check_error(S_ISDIR(fInfo.st_mode),"not dir");
 
  off_t max=0;
  off_t min=INT_MAX;
  
  check_error(traverse(argv[1],&max,&min),"traverse");
  
  int dif=(int)abs(max-min);
  printf("%d\n",dif);
exit(EXIT_SUCCESS);
}            
