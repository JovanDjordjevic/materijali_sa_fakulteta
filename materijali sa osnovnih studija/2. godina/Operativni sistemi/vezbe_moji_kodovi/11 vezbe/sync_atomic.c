#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<errno.h>
#include<pthread.h>
#include<stdatomic.h>

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

atomic_int globalSum;

void *threadFunc(void *arg){

    char *path=(char*)arg;
    
    FILE *in=fopen(path,"r");
      check_error(in!=NULL,"fopen failed");
    int localSum=0;
    int x;
    while(fscanf(in,"%d",&x)==1){
       localSum+=x;
    }
    check_error(feof(in)!=0,"feof");
    fclose(in);
    
    atomic_fetch_add(&globalSum,localSum);
    
    return NULL;
}


int main(int argc,char **argv){
   
   check_error(argc>1,"argumenti");
   
   int numThreads=argc-1;
   
   pthread_t *tids=malloc(numThreads*sizeof(pthread_t));
     check_error(tids!=NULL,"aloakcija tids");
     
   atomic_init(&globalSum,0);
   
   int i;
   for(i=0;i<numThreads;i++){
      check_thread(pthread_create(&tids[i],NULL,threadFunc,argv[i+1]),"thread create");    
   }
   
   
   for(i=0;i<numThreads;i++){
     check_thread(pthread_join(tids[i],NULL),"thread join failed");
   }
   
   printf("global sum: %d\n",atomic_load(&globalSum));
     
   free(tids);  
     
  exit(EXIT_SUCCESS);
}





