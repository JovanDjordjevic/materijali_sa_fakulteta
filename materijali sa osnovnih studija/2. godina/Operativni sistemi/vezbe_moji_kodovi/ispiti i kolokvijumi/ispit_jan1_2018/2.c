#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

#include<errno.h>
#include<time.h>
#include<string.h>
#include<ctype.h>
#include<sys/wait.h>
#include<signal.h>
#include<poll.h>
#include<limits.h>
#include<semaphore.h>
#include<sys/mman.h>
#include<pthread.h>

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
                
                
#define RD_END (0)
#define WR_END (1)
#define ARRAY_MAX (1024)

pthread_mutex_t globalLock=PTHREAD_MUTEX_INITIALIZER;
 const char *path;
 char *W;
 int poj=0;
 
 typedef struct{
    int start;
    int len;
 }info_t;
 
 
 void* threadFunc(void *arg){
    
    info_t *info=(info_t*)arg;
    int fd=open(path,O_RDONLY);
      check_error(fd!=-1,"open");
    
    check_error(lseek(fd,info->start,SEEK_SET)!=-1,"lseek");
    char *buf=malloc(info->len*sizeof(char));
      check_error(buf!=NULL,"thread alokacija");
      
    int readBytes=read(fd,buf,info->len);
      check_error(readBytes!=-1,"read");
    int local=0;
      
    char *x=strstr(buf,W);      
      if(x!=NULL) local++;
        
      while(x!=NULL){
         x=strstr(x+1,W);
         if(x!=NULL) local++;
      }
  
    
    
    check_error(pthread_mutex_lock(&globalLock)!=-1,"lock");
    poj+=local;
    check_error(pthread_mutex_unlock(&globalLock)!=-1,"unlock");
    
    close(fd);
  return NULL;
 }
  
int main(int argc, char **argv){
   
   check_error(argc==4,"args");
   
   path=argv[1];
   W=argv[2];
   int K=atoi(argv[3]);
  
   pthread_t *tids=malloc(K*sizeof(pthread_t));
     check_error(tids!=NULL,"alokacija1");
   info_t *info=malloc(K*sizeof(info_t));
     check_error(info!=NULL,"alokacija2");  
   
   unsigned size;
   struct stat fInfo;
     check_error(stat(path,&fInfo)!=-1,"stat");
   size=fInfo.st_size;
   
   int i;
   for(i=0;i<K;i++){
     
     info[i].start=(i)*(size/K);
     info[i].len=(size/K);
     
     check_error(pthread_create(&tids[i],NULL,threadFunc,&info[i])!=-1,"create");
   }
   
   
   for(i=0;i<K;i++){
     check_error(pthread_join(tids[i],NULL)!=-1,"join");  
   } 
   
   printf("%d\n",poj);
   
   free(tids);
   free(info);
  exit(EXIT_SUCCESS);
}
                 
