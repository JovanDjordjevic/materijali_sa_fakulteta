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
float globalMin=0;

typedef struct{
   float *red;
   int len;
   int n;
}threadData_t;

void* threadFunc(void *arg){
   threadData_t *curr=(threadData_t*)arg;
   float localMin=curr->red[0];
   int i;
   for(i=1;i<curr->len;i++){
       if(curr->red[i]<localMin) {localMin=curr->red[i];}
   }
   
   check_thread(pthread_mutex_lock(&globalLock),"lock");
     if(localMin<globalMin){  globalMin=localMin;}
   check_thread(pthread_mutex_unlock(&globalLock),"unlock");

 return NULL;
}



int main(int argc,char **argv){
   
   check_error(argc==2,"argumenti");
   FILE *in=fopen(argv[1],"r");
     check_error(in!=NULL,"fopen");
   int N;   //redovi
   int M;   //kolone
    
   fscanf(in,"%d %d",&N,&M); 

   float **matr=(float**)malloc(N*sizeof(float*));
     check_error(matr!=NULL,"aloakcija1");
   
   int i,j;
   for(i=0;i<N;i++){
     matr[i]=(float*)malloc(M*sizeof(float));
       check_error(matr[i]!=NULL,"alokacija 2");
   }
   
   
   for(i=0;i<N;i++){
      for(j=0;j<M;j++){
        fscanf(in,"%f",&matr[i][j]);
       }
   } 
 
   globalMin=matr[0][0];
   
   //pravimo tredove
   threadData_t *data=malloc(N*sizeof(threadData_t));
     check_error(data!=NULL,"alokacija3")
   
   pthread_t *tids=malloc(N*sizeof(pthread_t));
     check_error(tids!=NULL,"alokacija4");
   for(i=0;i<N;i++){    
     data[i].red=matr[i];
     data[i].len=M;
     data[i].n=i;
     
     check_thread(pthread_create(&tids[i],NULL,threadFunc,&data[i]),"create failed");
   }
   
   
   for(i=0;i<N;i++){
     check_thread(pthread_join(tids[i],NULL),"join failed");
   }
   

   /*for(i=0;i<N;i++){
      for(j=0;j<M;j++){
        printf("%.2f ",matr[i][j]);
      }
      printf("\n");
   } */ 
  
  printf("%f",globalMin);

  for(i=0;i<N;i++){
     free(matr[i]);
   } 
   free(matr);  
   fclose(in);
   check_thread(pthread_mutex_destroy(&globalLock),"destroy");
   
  exit(EXIT_SUCCESS);
}





