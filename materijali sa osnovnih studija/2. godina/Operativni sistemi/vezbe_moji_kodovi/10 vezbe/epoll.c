#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<errno.h>
#include<string.h>

#include<sys/epoll.h>

#define check_error(expr,userMsg)\
     do{\
       if(!(expr)){\
         fprintf(stderr,"%s\n",userMsg);\
         exit(EXIT_FAILURE);\
        }\
      }while(0);\

typedef struct{
  int num;
  int fd;
}epollData_t;
      
int main(int argc,char **argv){
   
   check_error(argc>1,"argumenti");
   
   int nfds=argc-1;
   int epollFds=epoll_create(nfds);
     check_error(epollFds!=-1,"epoll failed");
 
   struct epoll_event currentFd;
   
   int i;
   for(i=0;i<nfds;i++){
      
      int fd=open(argv[i+1],O_RDONLY | O_NONBLOCK);
        check_error(fd!=-1,"open fail");
      epollData_t *p=malloc(sizeof(epollData_t));
        check_error(p!=NULL,"alokacija");
      
      p->num=i;
      p->fd=fd;  
      
      memset(&currentFd,0,sizeof(struct epoll_event));
      currentFd.events=EPOLLIN | EPOLLERR | EPOLLHUP;
      currentFd.data.ptr=(void*)p;
      
      check_error(epoll_ctl(epollFds,EPOLL_CTL_ADD,fd,&currentFd)!=-1,"epoll ctl");    
   }
   
  struct epoll_event *readyEvents=malloc(sizeof(struct epoll_event)*10);
    check_error(readyEvents!=NULL,"malloc");
    
    while(nfds){
       int numActive=epoll_wait(epollFds,readyEvents,10,-1);
         check_error(numActive!=-1,"epoll wait");
         
         for(i=0;i<numActive;i++){
            if(readyEvents[i].events & EPOLLIN){
                epollData_t *p=(epollData_t*)readyEvents[i].data.ptr; 
                printf("spreman: %d\n",p->num);
                
                char buffer[1024];
                int readBytes=read(p->fd,buffer,1024);
                  check_error(readBytes!=-1,"read");
                buffer[readBytes]=0;
                printf("%s\n",buffer);  
            }
            else if(readyEvents[i].events & (EPOLLERR | EPOLLHUP)){
                epollData_t *p=(epollData_t*)readyEvents[i].data.ptr;
                printf("zatvaram: %d\n",p->num);
                
                close(p->fd);
                free(p);   //zasto ovde?
                nfds--;
            }
         
         }
    
    }
       
    close(epollFds);
    free(readyEvents);
     
  exit(EXIT_SUCCESS);
}  














