#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

#include<stdbool.h>
#include<dirent.h>
#include<string.h>

#define _XOPEN_SOURCE 700

#define check_error(expr,userMsg)\
                  do{\
                  if(!(expr)){\
                   fprintf(stderr,"%s\n",userMsg);\
                   exit(EXIT_FAILURE);\
                   }\
                   }while(0);


bool traverseDir(const char *path,unsigned *size){
 struct stat fInfo;
   if(lstat(path,&fInfo)==-1) {return false;} //inf o trenutnom, lstat zato sto nas ne interesuje da razresimo celu adresu pomocu stat
     *size+=fInfo.st_size;
  if(!S_ISDIR(fInfo.st_mode)) {return true;} //ako nije dir, prekiramo rekurziju
  
  DIR* dir=opendir(path);
   if(dir==NULL) {return false;}
   
 struct dirent *currEntry;
  while((currEntry=readdir(dir))!=NULL){
  
    char *newPath=malloc(strlen(path)+1+strlen(currEntry->d_name)+1);
    check_error(newPath!=NULL,"traverseDir malloc fail");
    
    strcpy(newPath,path);
    strcpy(newPath,"/");
    strcpy(newPath,currEntry->d_name);
    
    if(!strcmp(currEntry->d_name,".") || !strcmp(currEntry->d_name,"..")){
       if(stat(newPath,&fInfo)==-1){
          free(newPath);
          return false;
        }
      *size+=fInfo.st_size;
      free(newPath);
      continue;
    }
   bool state=traverseDir(newPath,size);
   free(newPath);
   
   if(state==false) {return false;} 
  }
  if(closedir(dir)==-1) {return false;}
  
  return true; //ako je SVE proslo kako treba
}



int main(int argc,char* argv[]){

check_error(argc==2,"argumenti");

struct stat fInfo;
check_error(stat(argv[1],&fInfo)!=-1,"stat fail");
check_error(S_ISDIR(fInfo.st_mode),"nije direktorijum");

unsigned size=0;
check_error(!traverseDir(argv[1],&size),"dir traverse fail");
printf("size=%u",size);

exit(EXIT_SUCCESS);
}

















