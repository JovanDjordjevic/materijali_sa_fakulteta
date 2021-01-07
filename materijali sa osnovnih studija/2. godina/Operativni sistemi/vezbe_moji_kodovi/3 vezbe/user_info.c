#include<stdio.h>
#include<stdlib.h>

#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<pwd.h>
#include<stdint.h>

#include<string.h> //zbog memcpy

#define check_error(expr,userMsg)\
                  do{\
                  if(!(expr)){\
                   fprintf(stderr,"%s\n",userMsg);\
                   exit(EXIT_FAILURE);\
                   }\
                   }while(0);


int main(int argc,char* argv[]){
  check_error(argc==2,"argumenti");
  
  struct passwd *PWD=getpwnam(argv[1]);
  check_error(PWD!=NULL,"pokazivac");
  
  /*moramo da napravimo lokalnu kopiju nase strukture
    zbog necega (?)
  */
  struct passwd *PWDCPY=malloc(sizeof(struct passwd));
   check_error(PWDCPY!=NULL,"alokacija kopije");
  memcpy(PWDCPY,PWD,sizeof(struct passwd)); 
  
  
  printf("%s\n",PWDCPY->pw_name);
  printf("%s\n",PWDCPY->pw_passwd);
  printf("%jd\n",(intmax_t)PWDCPY->pw_uid);
  printf("%jd\n",(intmax_t)PWDCPY->pw_gid);
  printf("%s\n",PWDCPY->pw_gecos);
  printf("%s\n",PWDCPY->pw_dir);
  printf("%s\n",PWDCPY->pw_shell);
  
  free(PWDCPY);

exit(EXIT_SUCCESS);
}













