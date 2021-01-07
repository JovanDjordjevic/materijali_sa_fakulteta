#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<math.h>

#define check_error(expr,userMsg)\
                  do{\
                  if(!(expr)){\
                   fprintf(stderr,"%s\n",userMsg);\
                   exit(EXIT_FAILURE);\
                   }\
                   }while(0);


int main(int argc,char* argv[]){
  check_error(argc==3,"argumenti");
  
 struct stat fInfo;
  check_error(stat(argv[1],&fInfo)!=-1,"stat");
  
 mode_t privileges=0;
  privileges |=fInfo.st_mode;  

if(argv[2][0]=='u'){
    if(argv[2][1]=='+'){
        if(argv[2][2]=='r'){
           privileges |= S_IRUSR;
        }
        else if(argv[2][2]=='w'){
           privileges |= S_IWUSR;
        }
        else if(argv[2][2]=='x'){
           privileges |= S_IXUSR;       
        }
        else{check_error(0,"U+ else");}
    }
    else if(argv[2][1]=='-'){
        if(argv[2][2]=='r'){
           privileges &= ~S_IRUSR;       
        }
        else if(argv[2][2]=='w'){
           privileges &= ~S_IWUSR;        
        }
        else if(argv[2][2]=='x'){
           privileges &= ~S_IXUSR;        
        }
        else{check_error(0,"U- else");}    
    }
    else {check_error(0,"else znak U");}
}


else if(argv[2][0]=='g'){
    if(argv[2][1]=='+'){
        if(argv[2][2]=='r'){
           privileges |= S_IRGRP;
        }
        else if(argv[2][2]=='w'){
           privileges |= S_IWGRP;
        }
        else if(argv[2][2]=='x'){
           privileges |= S_IXGRP;
        }
        else{check_error(0,"G+ else");}    
    }
    else if(argv[2][1]=='-'){
        if(argv[2][2]=='r'){
           privileges &= ~S_IRGRP;       
        }
        else if(argv[2][2]=='w'){
           privileges &= ~S_IWGRP;        
        }
        else if(argv[2][2]=='x'){
           privileges &= ~S_IXGRP;        
        }
        else{check_error(0,"G- else");}    
    }
    else {check_error(0,"else znak G");}    
}


else if(argv[2][0]=='o'){
    if(argv[2][1]=='+'){
        if(argv[2][2]=='r'){
           privileges |= S_IROTH;
        }
        else if(argv[2][2]=='w'){
           privileges |= S_IWOTH;
        }
        else if(argv[2][2]=='x'){
           privileges |= S_IXOTH;
        }
        else{check_error(0,"O+ else");}    
    }
    else if(argv[2][1]=='-'){
        if(argv[2][2]=='r'){
           privileges &= ~S_IROTH;      
        }
        else if(argv[2][2]=='w'){
           privileges &= ~S_IWOTH;        
        }
        else if(argv[2][2]=='x'){
           privileges &= ~S_IXOTH;                
        }
        else{check_error(0,"O- else");}    
    }
    else {check_error(0,"else znak O");}
}
else {check_error(0,"else1");}

   check_error(chmod(argv[1],privileges)!=-1,"chmod fail");   

exit(EXIT_SUCCESS);
}













