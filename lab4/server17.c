#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

struct item{
  char n[100];
  int p;
  int q;
};

void main(){
    int ssock,csock;
    FILE *f;
    struct item a[2];
    int i=0,n,len;
    char o[100];
    int d,t;


    f=fopen("First.txt","r");
    while(fscanf(f,"%s %d %d",a[i].n,&a[i].p,&a[i].q)!=EOF){
      printf("%s %d %d\n",a[i].n,a[i].p,a[i].q);
      i++;
    }
    n=i;

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


  	while(1){
      recv(csock,&o,sizeof(o),0);
      recv(csock,&d,sizeof(d),0);
      t=0;
      for(i=0;i<n;i++){
        if(strcmp(o,a[i].n)==0){
          if(a[i].q>=d){
            a[i].q-=d;
            t=a[i].p*d;
          }
        }
      }
      send(csock,&t,sizeof(t),0);
    }

}
