#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

#include<pwd.h>
#include<grp.h>
#include<string.h>
#define check_error(expr,userMsg)\
                  do{\
                  if(!(expr)){\
                   fprintf(stderr,"%s\n",userMsg);\
                   exit(EXIT_FAILURE);\
                   }\
                  }while(0);
                  
char *getU(uid_t uid){
 struct passwd *PWD=getpwuid(uid);
   check_error(PWD!=NULL,"uid fail"); 
 char *username=malloc(strlen(PWD->pw_name)+1);
   check_error(username!=NULL,"user null");
  strcpy(username,PWD->pw_name);
  return username;
}

char *getG(gid_t gid){
 struct group *GRP=getgrgid(gid);
   check_error(GRP!=NULL,"gid fail");
 char *group=malloc(strlen(GRP->gr_name)+1);
   check_error(group!=NULL,"group null");
  strcpy(group,GRP->gr_name);
  return group;
}

int main(int argc,char **argv){
  check_error(argc==2,"argumenti");
  struct stat fInfo;
  check_error(stat(argv[1],&fInfo)!=-1,"stat");
char *username=getU(fInfo.st_uid);
char *group=getG(fInfo.st_gid);
    
    printf("%s %s",username,group);

exit(EXIT_SUCCESS);
}








