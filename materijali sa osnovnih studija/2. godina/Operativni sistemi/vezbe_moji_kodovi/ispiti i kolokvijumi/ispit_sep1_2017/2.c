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
#include<sys/wait.h>
#include<signal.h>
#include<ctype.h>

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
#define MAX_SIZE (63)

pthread_mutex_t globalLock=PTHREAD_MUTEX_INITIALIZER;
int **matr;
int global=0;
int v=0;
int pozmax=0;

typedef struct{
  int col;
  int ln;
  char c;
}data_t;

void *threadFunc(void *argument){
    
    data_t *new=(data_t*)argument;
    
    int i;
    int local=0;
    for(i=0;i<v;i++){
      local+=matr[i][new->col];
    }    
    
    check_thread(pthread_mutex_lock(&globalLock),"lock");
      if(local>=global) {
        global=local;
        pozmax=new->col;
       }
    check_thread(pthread_mutex_unlock(&globalLock),"unlock");      
   
return NULL;
}
                  
int main(int argc, char **argv){
    
   int i,j;
   scanf("%d",&v);
   v=abs(v);
   
   matr=malloc(v*sizeof(int*));
     check_error(matr!=NULL,"alokacija1");
   for(i=0;i<v;i++){
     matr[i]=malloc(v*sizeof(int));
      check_error(matr!=NULL,"alokacija2");
   }  
   for(i=0;i<v;i++){
     for(j=0;j<v;j++){
       scanf("%d",&matr[i][j]);
       if(matr[i][j]!=0 && matr[i][j]!=1){
         check_error(0,"pogresan ulaz");
       }
     }
   }
   
   pthread_t *tids=malloc(v*sizeof(pthread_t));
     check_error(tids!=NULL,"alokacija3");
   data_t *data=malloc(v*sizeof(data_t));
     check_error(data!=NULL,"alokacija4");
   
   for(i=0;i<v;i++){
     data[i].col=i;
     //printf("making %d %d\n",i,data->col); 
       
   check_thread(pthread_create(&tids[i],NULL,threadFunc,&data[i]),"create");
   }  
   
   for(i=0;i<v;i++){
     check_thread(pthread_join(tids[i],NULL),"join");
   } 
   
   
   
   printf("%d\n",pozmax);
   
   
   
   /*for(i=0;i<v;i++){
     for(j=0;j<v;j++){
       printf("%d ",matr[i][j]);
     }
     printf("\n");
   }*/
      
   for(i=0;i<v;i++){
     free(matr[i]);
   }
   free(matr);
   check_thread(pthread_mutex_destroy(&globalLock),"destroy");  
  exit(EXIT_SUCCESS);
}
