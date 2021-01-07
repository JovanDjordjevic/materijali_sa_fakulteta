#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>


#define check_error(expr,userMsg)\
                  do{\
                  if(!(expr)){\
                   fprintf(stderr,"%s\n",userMsg);\
                   exit(EXIT_FAILURE);\
                   }\
                   }while(0);

//makeDir pravi direktorijum sa imenom koje damo kao argument komande linije u folderu gde se nalai a.out fajl

int makeDir(const char *path){
 mode_t mode = 0755;
 int dir=mkdir(path,mode);
 return dir;
}

int main(int argc,char* argv[]){

 check_error((argc==2),"argumenti");
 int dir;
 dir=makeDir(argv[1]);
check_error(dir!=-1,"mkdir fail");

exit(EXIT_SUCCESS);
}













