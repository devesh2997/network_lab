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
	char t[100]="Done";
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

	while(1){
		printf("Enter order\n");
		scanf("%s",s);
		if(strcmp(s,t)==0)
			break;
		scanf("%d",&n);
		send(sock,&s,sizeof(s),0);
		send(sock,&n,sizeof(n),0);
		recv(sock,&n,sizeof(n),0);
		printf("Transction= %d\n",n);
	}
	close(sock);

}
