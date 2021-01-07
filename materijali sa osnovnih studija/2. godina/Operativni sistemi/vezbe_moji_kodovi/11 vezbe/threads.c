#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<errno.h>
#include<string.h>

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

typedef struct{
   int threadNo;
}input_t;

typedef struct{
  int num;
}output_t;

void *threadFunc(void *argument){
   input_t* arg=(input_t *)argument;            //primimo arg
   
   output_t *retVal=malloc(sizeof(output_t)); //alociramo prostor odgovor (samo 1, ne numThreads puta)
     check_error(retVal!=NULL,"alokacija i tredu");
    
   printf("thread num: %d t\n ",arg->threadNo);         //uradimo nesto
   
   retVal->num=arg->threadNo+1000;  
 
  return retVal;    //vreatimo pokazivac na strukturu sa odgovorom
}

      
int main(int argc,char **argv){
   
     check_error(argc==2,"argumenti");
   int numThreads=atoi(argv[1]);
   
   pthread_t *tids=malloc(numThreads*sizeof(pthread_t));
     check_error(tids!=NULL,"alokacija");
   
   input_t *input=malloc(numThreads*sizeof(input_t));
     check_error(input!=NULL,"aloakcija2");
   
   int i;
   for(i=0;i<numThreads;i++){
      input[i].threadNo=i+1;
      check_thread(pthread_create(&tids[i],NULL,threadFunc,&input[i]),"pthread create failed");
   } 
   
   
   for(i=0;i<numThreads;i++){
   
   output_t *output=NULL;
     check_thread(pthread_join(tids[i],(void**)&output),"pthread join failed");   //zasto ovo radi i sa void* i sa void** konverzijom?????
   printf("thread finished : %d\n ",output->num);
   
   free(output);       //BITNO!!!!!!!
   }
   
  free(tids);
  free(input); 
        
  exit(EXIT_SUCCESS);
}  














