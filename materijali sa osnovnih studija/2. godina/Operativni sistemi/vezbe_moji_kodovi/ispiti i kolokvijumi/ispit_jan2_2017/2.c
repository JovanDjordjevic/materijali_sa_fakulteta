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
int globalMax;

//moglo je lakse ako bi nam matrica bila globalna
 
typedef struct{
  int **matr;
  int kolona;
  int N;
}threadData_t; 
 
void *threadFunc (void *arg){
   
   threadData_t *data=(threadData_t*)arg;
   int i;
   int localMax=0;
   int col=data->kolona;
   
   for(i=0;i<data->N;i++){
      localMax+=data->matr[i][col];
   }
   
   check_thread(pthread_mutex_lock(&globalLock),"lock");
   
   if(localMax>globalMax) globalMax=localMax;
   
   check_thread(pthread_mutex_unlock(&globalLock),"unlock");

return NULL;
}
            
int main(int argc,char **argv){
       
      check_error(argc==2,"args");
      
    FILE *in=fopen(argv[1],"r");
      int N; //redovi
      int M; //kolone
    fscanf(in,"%d%d",&N,&M);
    
      int **matr=malloc(N*sizeof(int*));
        check_error(matr!=NULL,"aloakcija1"); 
     
     int i,j;
     for(i=0;i<N;i++){
       matr[i]=malloc(M*sizeof(int));
         check_error(matr[i]!=NULL,"aloakcija 2");
     }
     
     for(i=0;i<N;i++){
       for(j=0;j<M;j++){
         fscanf(in,"%d",&matr[i][j]);
       }
     }
     
     globalMax=matr[0][0];
     
     pthread_t *tids=malloc(M*sizeof(pthread_t));
       check_error(tids!=NULL,"alokacija 3");
     threadData_t *data=malloc(M*sizeof(threadData_t));
       check_error(data!=NULL,"alokacija 4");
     
     for(i=0;i<M;i++){
       data[i].matr=matr;
       data[i].N=N;
       data[i].kolona=i;  
       check_thread(pthread_create(&tids[i],NULL,threadFunc,&data[i]),"create failed");
     }
     
     
     for(i=0;i<M;i++){
       check_thread(pthread_join(tids[i],NULL),"join failed");
     }
     
     printf("%d\n",globalMax);
     
    /* for(i=0;i<N;i++){
       for(j=0;j<M;j++){
         fprintf(stdout,"%d ",matr[i][j]);
       }
       printf("\n");
     }*/

    for(i=0;i<N;i++){
      free(matr[i]);
    }  
    free(matr);
    fclose(in);
    check_thread(pthread_mutex_destroy(&globalLock),"destroy");  
    exit(EXIT_SUCCESS);
}





