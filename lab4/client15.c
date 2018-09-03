#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<string.h>

void main(){
	int sock;
	unsigned int len;
	char s[100];
	char c[1000];
	FILE *f;
	char x;
	int i,n=0;

	struct sockaddr_in client;
	if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket: ");
		exit(-1);
	}

	client.sin_family=AF_INET;
	client.sin_port=htons(10000);
	client.sin_addr.s_addr=INADDR_ANY;

	bzero(&client.sin_zero,0);


	len=sizeof(struct sockaddr_in);
	if((connect(sock,(struct sockaddr *)&client,len))==-1){
		perror("connect: ");
		exit(-1);
	}

	printf("Enter file name\n");
	scanf("%s",s);
	f=fopen(s,"r");
	if(f==0){
		exit(-1);
	}
	x=fgetc(f);
  while(x!=EOF){
    printf("%c",x);
		c[n++]=x;
    x=fgetc(f);
  }
	fclose(f);
	send(sock,&c,sizeof(c),0);
	close(sock);

}
