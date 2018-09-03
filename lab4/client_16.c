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
	char password[100];
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
	bool loggedIn = false;
	while(1){
		if(!loggedIn){
			printf("Enter the password : ");
			scanf("%s",password);
			send(sock,&password,sizeof(password),0);
			bool flag;
			recv(sock,&flag,sizeof(flag),0);
			if(flag){
				loggedIn = true;
				printf("password correct!\n");
				
			}else{
				printf("password incorrect!\n");
				printf("Invalid password!\n");
			}
		}else{
			printf("Enter message : ");
			char input[100];
			scanf("%s",input);
			send(sock,&input,sizeof(input),0);
			char res[100];
			recv(sock,&res,sizeof(res),0);
			printf("%s\n",res);
		}
		
	}
}
