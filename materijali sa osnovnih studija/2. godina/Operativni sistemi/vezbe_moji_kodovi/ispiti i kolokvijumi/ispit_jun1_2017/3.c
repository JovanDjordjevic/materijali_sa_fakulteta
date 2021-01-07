//POLA NEDOVRSEN

#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<sys/wait.h>
#include<pthread.h>
#include<errno.h>

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

typedef struct{
  int **matr3;
  int rows3;
  int cols3;
  
}threadData_t;

void* threadFunc(void *arg){
   
}



int main(int argc,char **argv){
      
   int N,M,K;
   int i,j;
   
   scanf("%d %d",&N,&M);   //MATR 1
   
   int **matr1=malloc(N*sizeof(int*));
     check_error(matr1!=NULL,"aloakcija 11");
   for(i=0;i<N;i++){
     matr1[i]=malloc(M*sizeof(int));
       check_error(matr1[i]!=NULL,"aloakcija 12");
   } 
   for(i=0;i<N;i++){
      for(j=0;j<M;j++){
        scanf("%d",&matr1[i][j]);
      }
   } 
   scanf("%d %d",&M,&K);   //MATR 2
   
   int **matr2=malloc(M*sizeof(int*));
     check_error(matr2!=NULL,"aloakcija 21");
   for(i=0;i<M;i++){
     matr2[i]=malloc(K*sizeof(int));
       check_error(matr2[i]!=NULL,"aloakcija 22");
   } 
   for(i=0;i<M;i++){
      for(j=0;j<K;j++){
        scanf("%d",&matr2[i][j]);
      }
   }  
   int **matr3=malloc(N*sizeof(int*));   //REZ MATRICA
     check_error(matr1!=NULL,"aloakcija 11");
   for(i=0;i<N;i++){
     matr1[i]=malloc(M*sizeof(int));
       check_error(matr1[i]!=NULL,"aloakcija 12");
   }  
  
   
   int numThreads=N*K;   //tredovi
   pthread_t *tids=malloc(numThreads*sizeof(pthread_t));
    check_error(tids!=NULL,"aloakcija tids");
  threadData_t *data=malloc(numThreads*sizeof(threadData_t));
    check_error(data!=NULL,"aloakcija data");
    
   for(i=0;i<numThreads;i++){
        
      
      check_thread(pthread_create(&tids[i],NULL,threadFunc,&data[i]),"create failed");   
   }
  
  for(i=0;i<numThreads;i++){
      check_thread(pthread_join(tids[i],NULL),"join failed");   
   }
  
  
  /*printf("\n");
  printf("%d %d %d\n",N,M,K);
  printf("\n");
  for(i=0;i<N;i++){
      for(j=0;j<M;j++){
        printf("%d ",matr1[i][j]);
      }
      printf("\n");
   } 
   printf("\n");  

  for(i=0;i<M;i++){
      for(j=0;j<K;j++){
        printf("%d ",matr2[i][j]);
      }
      printf("\n");
   } */  
  
   for(i=0;i<N;i++){
     free(matr1[i]);
   } 
   for(j=0;j<M;j++){
     free(matr2[j]);
   } 
   free(matr1);
   free(matr2);   
  check_thread(pthread_mutex_destroy(&globalLock),"destroy failed");   
  exit(EXIT_SUCCESS);
}





