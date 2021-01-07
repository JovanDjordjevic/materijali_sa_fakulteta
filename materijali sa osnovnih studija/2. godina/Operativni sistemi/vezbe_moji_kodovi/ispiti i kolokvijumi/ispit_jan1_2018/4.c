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
#include<sys/wait.h>
#include<signal.h>
#include<poll.h>
#include<limits.h>

#define check_error(expr,userMsg)\
                do{\
                  if(!(expr)){\
                    fprintf(stderr,"%s\n",userMsg);\
                    exit(EXIT_FAILURE);\
                   }\
                 }while(0);

#define RD_END (0)
#define WR_END (1)

int max=INT_MIN;
int pozmax=-1;


int main(int argc, char **argv){

  check_error(argc>1,"args");
  
  int nfds=argc-1;
  struct pollfd *pollfds=malloc(nfds*sizeof(struct pollfd));
    check_error(pollfds!=NULL,"alokacija");
  int *niz=malloc(nfds*sizeof(int));
    check_error(niz!=NULL,"aloakcija2");
    
  int i;
  for(i=0;i<nfds;i++){
    
    niz[i]=0;
    
    int fd=open(argv[i+1],O_RDONLY | O_NONBLOCK);
      check_error(fd!=-1,"open"); 
    pollfds[i].fd=fd;
    pollfds[i].events=POLLIN|POLLERR|POLLHUP;
    pollfds[i].revents=0;
    
  }  
  
  int active=nfds;
  
  while(active){
    check_error(poll(pollfds,nfds,-1)!=-1,"poll failed");
    
    for(i=0;i<nfds;i++){   
         
         if(pollfds[i].revents & POLLIN){
           
           char buf[2048]; 
           int readBytes=read(pollfds[i].fd,buf,2048);
             check_error(readBytes!=-1,"read");
           
           niz[i]+=readBytes;
           if(niz[i]>max) {
              max=niz[i];
              pozmax=i+1;
           }
              
           
           pollfds[i].revents=0;
         }
         else if((pollfds[i].revents & POLLERR) || (pollfds[i].revents & POLLHUP)){
            
            close(pollfds[i].fd);
            pollfds[i].fd=-1;
            pollfds[i].events=0;
            pollfds[i].revents=0;
            active--;
         }
         
    }
  
  
  }
  
  char *ptr=strrchr(argv[pozmax],'/');
  printf("%s\n",ptr==NULL ? argv[pozmax] : ptr+1);
  
  for(i=0;i<nfds;i++){
    if(pollfds[i].fd!=-1) close(pollfds[i].fd);
  }
  free(pollfds);
  free(niz);
  exit(EXIT_SUCCESS);
}
                 
