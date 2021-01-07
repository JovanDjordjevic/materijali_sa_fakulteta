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


bool traverseDir (const char *path, unsigned *size){
 
    struct stat fInfo;
    if(lstat(path,&fInfo)==-1){ return false;}
   
   *size+=fInfo.st_size;
   if(!S_ISDIR(fInfo.st_mode)) {return true;}
   
   DIR *dir=opendir(path);
   if(dir==NULL) {return false;}
   
   if(chdir(path)==-1) return true; //chdir stavlja trenutni radni direktorijum na "path", ako je -1 znaci da nije uspeo da promeni dir(znaci da u "path" nije dir)
   
   struct dirent *currEntry;
   while( (currEntry=readdir(dir)) !=NULL){
     if(!strcmp(currEntry->d_name,".") || !strcmp(currEntry->d_name,"..")){
          if(stat(currEntry->d_name,&fInfo)==-1) {return false;}
     *size+=fInfo.st_size;
     continue; 
       }
   bool state=traverseDir(currEntry->d_name,size);
   if(state==false) {return false;}
   }
   if (chdir("..")==-1) {return false;}
   if (closedir(dir)==-1) {return false;}  

return true;   
}


int main(int argc,char* argv[]){
 
 check_error(argc==2,"argumenti");
 struct stat fInfo;
 check_error(stat(argv[1],&fInfo)!=-1,"stat fail");
 
 check_error(S_ISDIR(fInfo.st_mode),"nije direktorijum");
 
 unsigned size=0;
 check_error(traverseDir(argv[1],&size),"traverseDir fail");
 printf("size= %u",size);

exit(EXIT_SUCCESS);
}

















