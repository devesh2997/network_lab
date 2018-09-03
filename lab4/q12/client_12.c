#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <math.h>

int main(){
    int sock;
	unsigned int len;
	char ch;
	
	struct sockaddr_in client;
	if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket: ");
		exit(-1);
	}

	client.sin_family = AF_INET;
	client.sin_port=htons(10000);
	client.sin_addr.s_addr=INADDR_ANY;
	bzero(&client.sin_zero,0);

	len=sizeof(struct sockaddr_in);
	if((connect(sock,(struct sockaddr*)&client,len))==-1){
		perror("connect: ");
		exit(-1);
	}

	char q[150];
	int n;
	n=3;
	while(n--){
		printf("Enter a question:\n");
		gets(q);
		send(sock,&q,sizeof(q),0);
		char res[150];
		recv(sock,&res,sizeof(res),0);
		if(res!=NULL)printf("%s\n",res);
		else printf("Try again\n");
	}
}