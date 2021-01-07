//deluje da radi ali ne prolazi na grejderu

#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#include<errno.h>
#include<pthread.h>
#include<string.h>

#define check_error(expr,userMsg)\
                do{\
                  if(!(expr)){\
                     fprintf(stderr,"%s\n",userMsg);\
                     exit(EXIT_FAILURE);\
                    }\
                  }while(0);
                  
#define check_thread(err,userMsg)\
                do{\
                  int _err=err;\
                  if(_err){\
                    errno=_err;\
                    check_error(0,userMsg);\
                   }\
                  }while(0);

pthread_mutex_t globalLock=PTHREAD_MUTEX_INITIALIZER;                  
int globalArray[2048];
int pos=0;

typedef struct{
  int start;
  int len;
  const char* path;
}data_t;

void *threadFunc(void *argument){
    data_t *arg=(data_t*)argument;
    
    int fd=open(arg->path,O_RDONLY);
      check_error(fd!=-1,"open");
      
    FILE *in=fdopen(fd,"r");
      check_error(in!=NULL,"fdopen");
    check_error(fseek(in,arg->start,SEEK_SET)!=-1,"lseek");    
    
    int i;
    for(i=0;i<arg->len-2;i++){
      char c1,c2,c3;
      
      fscanf(in,"%c%c%c",&c1,&c2,&c3);
      if(c1=='t'){
         if( (c2=='a' && c3=='g') || (c2=='a' && c3=='a') || (c2=='g' && c3=='a') ){
            
            check_thread(pthread_mutex_lock(&globalLock),"lock");
               globalArray[pos]=ftell(in)-3;
               
               pos++;
            check_thread(pthread_mutex_unlock(&globalLock),"unlock");
         }
      }   
      
      check_error(fseek(in,-2,SEEK_CUR)!=-1,"lseek");
    }
    
  fclose(in);  
  
 return NULL;
}

                  
int main(int argc, char **argv){

     check_error(argc==3,"args");
   
   int n=atoi(argv[1]);
   int M;
   struct stat fInfo;
     check_error(stat(argv[2],&fInfo)!=-1,"stat fail");
   
   M=fInfo.st_size;
   
   pthread_t *tids=malloc(n*sizeof(pthread_t));
     check_error(tids!=NULL,"alokacija");
   data_t *data=malloc(n*sizeof(data_t));
     check_error(data!=NULL,"alokacija 2");
     
   
   int i;
   for(i=0;i<n;i++){
     data[i].start=i*(M/n);
     data[i].len=M/n; 
     data[i].path=argv[2];    
     check_thread(pthread_create(&tids[i],NULL,threadFunc,&data[i]),"create");  
   }  
   
   for(i=0;i<n;i++){
     check_thread(pthread_join(tids[i],NULL),"join");
   }
 
 for(i=0;i<=pos;i++){
    printf("%d ",globalArray[i]);
 }
 printf("\n");
 
 free(tids);
 check_thread(pthread_mutex_destroy(&globalLock),"destroy");
 
 
  exit(EXIT_SUCCESS);
}
