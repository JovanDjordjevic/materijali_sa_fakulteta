//petlja se ne ponasa kako treba

#define _XOPEN_SOURCE
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
#include<semaphore.h>
#include<sys/mman.h>
#include<sys/poll.h>
#include<limits.h>
#include<stdint.h>

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

int max=INT_MIN;
int maxfifo=0;
                  
int main(int argc, char **argv){
    
    check_error(argc>1,"args");
    
    int nfds=argc-1;
    int i;
    struct pollfd *pollFds=malloc(nfds*sizeof(struct pollfd));
      check_error(pollFds!=NULL,"alokacija");
    for(i=0;i<nfds;i++){
       
       int fd=open(argv[i+1],O_RDONLY|O_NONBLOCK);
         check_error(fd!=-1,"open");
       pollFds[i].fd=fd;
       pollFds[i].events=POLLIN|POLLERR|POLLHUP;
       pollFds[i].revents=0;
                       
    }
    
    while(nfds){
       
           printf("bean\n"); 
      check_error(poll(pollFds,nfds,-1)!=-1,"poll");           
           printf("bean1\n");
           
      for(i=0;i<nfds;i++){
          
        if(pollFds[i].revents & POLLIN){
          
          printf("bean2\n");
          
          FILE *in=fdopen(pollFds[i].fd,"r");
            check_error(in!=NULL,"in");
          int x;
          fscanf(in,"%d",&x);
          if(x>max) {
             max=x;
             maxfifo=i+1;
          }
          pollFds[i].revents=0; 
          fclose(in); 
        }
        else if((pollFds[i].revents & POLLERR) || (pollFds[i].revents & POLLHUP)){
           close(pollFds[i].fd);
           pollFds[i].fd=-1;
           pollFds[i].events=0;
           pollFds[i].revents=0;
           nfds--;
        }          
      }
           
    }
   
    char *fifo=argv[maxfifo];
    char *ptr;
    char *str=malloc(strlen(fifo)+1);
      check_error(str!=NULL,"str alokacija");
    
    ptr=strrchr(fifo,'/');
       if(ptr==NULL)
          strcpy(str,fifo);
       else 
          strcpy(str,ptr+1);   
    
    printf("%d %s\n",max,str);
    
    
    for(i=0;i<nfds;i++){
       if(pollFds[i].fd!=-1) close(pollFds[i].fd);
    }
    free(pollFds); 
  exit(EXIT_SUCCESS);
}
