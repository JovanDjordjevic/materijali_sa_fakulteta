#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#include<errno.h>
#include<string.h>

#include<poll.h>

#define check_error(expr,userMsg)\
     do{\
       if(!(expr)){\
         fprintf(stderr,"%s\n",userMsg);\
         exit(EXIT_FAILURE);\
        }\
      }while(0);\

      
int main(int argc,char **argv){
   
   check_error(argc>1,"argumenti");
   int nfds=argc-1;
   
   struct pollfd* fds=malloc(nfds*sizeof(struct pollfd));
     check_error(fds!=NULL,"alokacija");
     
   int i;
   for(i=0;i<nfds;i++){
      int fd=open(argv[i+1],O_RDONLY | O_NONBLOCK);
        check_error(fd!=-1,"open [i]");
      fds[i].fd=fd;
      fds[i].events= POLLERR | POLLHUP| POLLIN;      //postiji i POLLOUT ako hocemo da gledamoz a pisanje, fd treba biti otvoren u WRONLY modu
      fds[i].revents= 0;
   }   
    
  while(1){
    int retVal=poll(fds,nfds,-1);
      check_error(retVal!=-1,"poll failed");
      
      int breakloops=0;
      for(i=0;i<nfds;i++){
          
          if(fds[i].revents & POLLIN){
              char buffer[1024];
              int readBytes=read(fds[i].fd,buffer,1024);
                check_error(readBytes!=-1,"read fail");
              buffer[readBytes]=0;
              
              printf("%d: %s\n",i,buffer);
              if(!strcmp(buffer,"quit\n")){
                  breakloops=1;
                  break;
              }
             fds[i].revents=0;    //OBAVEZNO resetujemo dogadjaj              
          }
          else if((fds[i].revents & POLLERR) || (fds[i].revents & POLLHUP) ){
              close(fds[i].fd);
              fds[i].fd=-1;
              fds[i].events=0;
              fds[i].revents=0;
          }      
      }
      
   if(breakloops) break; 
  }

     for(i=0;i<nfds;i++){
       close(fds[i].fd);
     }
   free(fds);  

  exit(EXIT_SUCCESS);
}  



