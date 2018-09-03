#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>


void main(){
    int ssock,csock;
    FILE *f;
    int i=0,n,len;
    char o[1000];
    char c[1000];
    char t[1000];
    char nf[100]="No result";

    struct sockaddr_in server,client;

  	if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1){
  		perror("socket: is not created");
  		exit(-1);
  	}

  	server.sin_family=AF_INET;
  	server.sin_port=htons(10000);
  	server.sin_addr.s_addr=INADDR_ANY;

  	bzero(&server.sin_zero,0);

  	len=sizeof(struct sockaddr_in);

  	if((bind(ssock,(struct sockaddr *)&server,len))==-1){
  		perror("bind: ");
  		exit(-1);
  	}

  	if((listen(ssock,5))==-1){
  		perror("listen: ");
  		exit(-1);
  	}

  	if((csock=accept(ssock,(struct sockaddr *)&client,&len))==-1){
  		perror("accept: ");
  		exit(-1);
  	}


  	recv(csock,&o,sizeof(o),0);
    f=fopen("database.txt","r");
    while(fscanf(f,"%[^\n]\n",c)!=EOF){
      fscanf(f,"%[^\n]\n",t);
      if(strcmp(c,o)==0){
        send(csock,&t,sizeof(t),0);
      }
    }
    send(csock,&nf,sizeof(nf),0);
    close(csock);
}
