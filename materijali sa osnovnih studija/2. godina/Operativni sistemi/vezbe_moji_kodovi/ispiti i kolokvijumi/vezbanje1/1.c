//racuna globalnu ispravno ali negde gresim sa ispisivanjem lokalih

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
#include<semaphore.h>
#include<sys/mman.h>
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

typedef struct{
  const char *path;
}threadData_t;

typedef struct{
  int loc;
}ret_t;

void *threadFunc(void *arg){
   threadData_t *data=(threadData_t*)arg;
   
   //printf("%s\n",data->path);
   
   int fd=open(data->path,O_RDONLY);
     check_error(fd!=-1,"open");
   FILE *in=fdopen(fd,"r");
     check_error(in!=NULL,"fdopen");
   char c;
   int plus,minus,local;
    while(fscanf(in,"%c",&c)==1){
       if(c=='+') plus++;
       else if(c=='-') minus++;
       else continue;
    }
   local=plus-minus;
   
   atomic_fetch_add(&globalSum,local);
   
   ret_t *rez=malloc(sizeof(ret_t));
       check_error(rez!=NULL,"aloakcija3");
      
   rez->loc=local;
   
   fclose(in);
   return rez;
}

            
int main(int argc,char **argv){
       
     check_error(argc>1,"args");
     
     int numThreads=argc-1;
     pthread_t *tids=malloc(numThreads*sizeof(pthread_t));
       check_error(tids!=NULL,"aloakcija1");     
     
     threadData_t *data=malloc(numThreads*sizeof(threadData_t));
       check_error(data!=NULL,"aloakcija2");   
            
     atomic_init(&globalSum,0);
     
     int i;
     for(i=0;i<numThreads;i++){        //create
       data[i].path=argv[i+1];
       
       
     check_thread(pthread_create(&tids[i],NULL,threadFunc,&data[i]),"create");
     }
     
     int *niz=malloc(numThreads*sizeof(int));
       check_error(niz!=NULL,"alokacija4");
     
     for(i=0;i<numThreads;i++){  //join
       ret_t *rez=NULL;
       
       check_thread(pthread_join(tids[i],(void**)&rez),"join");
       
       niz[i]=rez[i].loc;

       free(rez); //!!!!!!!!!!!!!!!!!!!!
     }
     
     
     for(i=0;i<numThreads;i++){
       printf("%d\n",niz[i]);
     }
     printf("%d\n",atomic_load(&globalSum));
     
      
      free(tids);
      free(data);
    exit(EXIT_SUCCESS);
}




