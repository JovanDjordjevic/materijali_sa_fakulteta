#define _XOPEN_SOURCE 700

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdbool.h>

#include<string.h>
#include<dirent.h>

#define check_error(expr,usrMsg)\
            do{\
              if(!(expr)){\
                fprintf(stderr,"%s\n",usrMsg);\
                exit(EXIT_FAILURE);\
              }\
            }while(0);

char *ext=NULL;

bool traverse(const char *path,int *sum){
  
  struct stat fInfo;
   if(lstat(path,&fInfo)==-1) return false;
   
   if(S_ISREG(fInfo.st_mode)){
   char *point=strrchr(path,'.');
    if( point!=NULL && !strcmp(ext,point) ) *sum+=1;
    }
    if(!S_ISDIR(fInfo.st_mode)) return true;
   
  DIR *dir=opendir(path);
  if(dir==NULL) return false; 
  
  if(chdir(path)==-1) return false;
   
   struct dirent *current=NULL;
   while( (current=readdir(dir))!=NULL ){
                  
         if(!strcmp(current->d_name,".") || !strcmp(current->d_name,"..") ) continue;
         
         bool state=traverse(current->d_name,sum);        
          /*if(state==true) printf("true\n");
           else printf("false\n");*/
         if(state==false) return false;
   }
if(chdir("..")==-1) return false;
if(closedir(dir)==-1) return false;

return true;

}


int main(int argc,char **argv){
     check_error(argc==3,"argumenti");
     ext=argv[2];
     struct stat fInfo;
     check_error(stat(argv[1],&fInfo)!=-1,"stat");     
     check_error(S_ISDIR(fInfo.st_mode),"nije dir");
  int sum=0;
  
  check_error(traverse(argv[1],&sum),"traverse");
  
  printf("%d\n",sum);
  
 exit(EXIT_SUCCESS);
}
