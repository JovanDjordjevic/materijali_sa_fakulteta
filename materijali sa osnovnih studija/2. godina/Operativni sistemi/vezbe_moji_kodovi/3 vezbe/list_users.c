#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>


#include<pwd.h>
#include<stdint.h>

#define _XOPEN_SOURCE_ 700 //moramo da ukljucimo zbog getpwent,setpwent,endpwent

#define check_error(expr,userMsg)\
                  do{\
                  if(!expr){\
                   fprintf(stderr,"%s\n",userMsg);\
                   exit(EXIT_FAILURE);\
                   }\
                   }while(0);



int main(int argc,char* argv[]){

setpwent();
 struct passwd *current;
 while((current=getpwent())!=NULL){
   printf("---------------\n");
  printf("%s\n",current->pw_name);
  printf("%s\n",current->pw_passwd);
  printf("%jd\n",(intmax_t)current->pw_uid);
  printf("%jd\n",(intmax_t)current->pw_gid);
  printf("%s\n",current->pw_gecos);
  printf("%s\n",current->pw_dir);
  printf("%s\n",current->pw_shell);
   printf("---------------\n");
 }

endpwent();

exit(EXIT_SUCCESS);
}













