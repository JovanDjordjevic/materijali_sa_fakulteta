#include<stdio.h>
#include<stdlib.h>

#include<pwd.h>
#include<grp.h>
#include<stdint.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

#include<string.h>
#include<time.h>

#define MAXSIZE 1024
#define check_error(expr,userMsg)\
                  do{\
                  if(!(expr)){\
                   fprintf(stderr,"%s\n",userMsg);\
                   exit(EXIT_FAILURE);\
                   }\
                   }while(0);

char *getUsername(uid_t uid){
 struct passwd *PWD=getpwuid(uid);
  check_error(PWD!=NULL,"getpwd fail");
 char *Username=malloc(strlen(PWD->pw_name)+1);
  check_error (Username!=NULL,"malloc uid");
  strcpy(Username,PWD->pw_name);
  return Username;
}

char *getGroupname(gid_t gid){
 struct group *GRP=getgrgid(gid);
  check_error(GRP!=NULL,"getgrnam fail");
 char *grpName=malloc(strlen(GRP->gr_name)+1);
  check_error(grpName!=NULL,"grp alokacija");
  strcpy(grpName,GRP->gr_name);
 return grpName;
}


void fileInfo(const char *pathname,char **s){
   check_error(*s==NULL,"pokazivac");
/* *s=malloc(MAXSIZE);
   check_error(*s!=NULL,"alokacija");
*/
  struct stat fInfo;
  check_error(stat(pathname,&fInfo)!=-1,"stat fail");  

char *myStr=malloc(MAXSIZE);
 check_error(myStr!=NULL,"alokacijax");
 memset(myStr,0,MAXSIZE);

 int bytesWritten=0;
 bytesWritten+=sprintf(myStr+bytesWritten,"%s ", "-rwxrwxrwx");
 
switch(fInfo.st_mode & S_IFMT){
  case S_IFREG: myStr[0]='-'; break;
  case S_IFDIR: myStr[0]='d'; break;
  case S_IFCHR: myStr[0]='c'; break;
  case S_IFBLK: myStr[0]='b'; break;
  case S_IFLNK: myStr[0]='l'; break;
  case S_IFSOCK: myStr[0]='s'; break;
  case S_IFIFO: myStr[0]='p'; break;
  default: break;
}

if(!(fInfo.st_mode & S_IRUSR)) myStr[1]='-';
if(!(fInfo.st_mode & S_IWUSR)) myStr[2]='-';
if(!(fInfo.st_mode & S_IXUSR)) myStr[3]='-';

if(!(fInfo.st_mode & S_IRGRP)) myStr[4]='-';
if(!(fInfo.st_mode & S_IWGRP)) myStr[5]='-';
if(!(fInfo.st_mode & S_IXGRP)) myStr[6]='-';

if(!(fInfo.st_mode & S_IROTH)) myStr[7]='-';
if(!(fInfo.st_mode & S_IWOTH)) myStr[8]='-';
if(!(fInfo.st_mode & S_IXOTH)) myStr[9]='-';



bytesWritten+=sprintf(myStr+bytesWritten,"%jd ",(intmax_t)fInfo.st_size);


char *Username=getUsername(fInfo.st_uid);
 bytesWritten+=sprintf(myStr+bytesWritten,"%s ",Username);
free(Username);

char *Groupname=getGroupname(fInfo.st_gid);
 bytesWritten+=sprintf(myStr+bytesWritten,"%s ",Groupname);
free(Groupname);

char *t=ctime(&(fInfo.st_atime));
 bytesWritten+=sprintf(myStr+bytesWritten,"%s\n",t);

*s=myStr;
}


int main(int argc,char* argv[]){

 check_error(argc==2,"argumenti");
 
 char *s=NULL;
 fileInfo(argv[1],&s);
 printf("%s",s);
 free(s);

exit(EXIT_SUCCESS);
}













