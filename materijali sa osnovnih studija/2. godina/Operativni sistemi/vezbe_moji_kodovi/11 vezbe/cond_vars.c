//ne radi

#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<errno.h>
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
              
int globalDataCount=0;
int globalArray[1024];
pthread_cond_t globalSignaler=PTHREAD_COND_INITIALIZER;
pthread_mutex_t globalLock=PTHREAD_MUTEX_INITIALIZER;


void *threadFunc(void *arg){
  int id=(int)(intptr_t)arg;
  
  while(1){
    check_error(pthread_mutex_lock(&globalLock),"lock failed func");
    while(globalDataCount==0){
        check_thread(pthread_cond_wait(&globalSignaler,&globalLock),"wait");
    }
    if(globalDataCount==-1){
       check_error(pthread_mutex_unlock(&globalLock),"unlock");
       break;
    }
    printf("thread id: %d \n",id);
    int i;
    for(i=0;i<globalDataCount;i++){
      printf("%d ",globalArray[i]*globalArray[i]);
    }
    printf("\n");
    globalDataCount=0;
    check_error(pthread_mutex_unlock(&globalLock),"unlock");
  }
 printf("thread exited: %d\n",id); 
 return NULL;
}

int main(int argc,char **argv){
   
   check_error(argc==2,"argumenti");
   
   int numThreads=atoi(argv[1]);
   pthread_t *tids=malloc(numThreads*sizeof(pthread_t));
     check_error(tids!=NULL,"aloakcija");
     
   int i;
   for(i=0;i<numThreads;i++){
      check_thread(pthread_create(&tids[i],NULL,threadFunc,(void*)(intptr_t)i),"thread crate failed");   //BITNO (intptr_t)
   }   
   
   char *linija=NULL;
   size_t len=0;
   
     while(getline(&linija,&len,stdin)!=-1){
       
       int bytesRead=0;
       int totalBytes=0;
       
       check_thread(pthread_mutex_lock(&globalLock),"lock failed1");
         sscanf(linija,"%d%n",&globalDataCount,&bytesRead);
         totalBytes+=bytesRead;
         
         if(globalDataCount==-1){
           check_thread(pthread_mutex_unlock(&globalLock),"unlock failed");
           check_thread(pthread_cond_broadcast(&globalSignaler),"broadcast"); //budimo sve tredove
           break; 
         }
        for(i=0;i<globalDataCount;i++){
           sscanf(linija+totalBytes,"%d%n",&globalArray[i],&bytesRead);
           totalBytes+=bytesRead;
        }
       check_thread(pthread_mutex_unlock(&globalLock),"unlock");
       check_thread(pthread_cond_signal(&globalSignaler),"signal"); //budimo samo jedan tred
   }
   
   
   for(i=0;i<numThreads;i++){
     check_thread(pthread_join(tids[i],NULL),"join");
   }
   
   free(linija);
   free(tids);
   check_thread(pthread_mutex_destroy(&globalLock),"destroy failed");
  exit(EXIT_SUCCESS);
}





