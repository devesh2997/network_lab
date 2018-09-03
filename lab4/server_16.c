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

bool match(char password[100], char input[100]){
	int i=0;
	while(i<100){
		if(password[i]=='\0' && input[i]=='\0')break;
		if(password[i]=='\0' || input[i]=='\0' || password[i]!=input[i])return false;
		i++;
	}
	return true;
}


int main(){
	int ssock,csock;
	char password[] = "password";
	char input[100];
	unsigned int len;

	struct sockaddr_in server,client;
	if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket: ");
		exit(-1);
	}

	client.sin_family = AF_INET;
	client.sin_port=htons(10000);
	client.sin_addr.s_addr=INADDR_ANY;
	bzero(&server.sin_zero,0);

	len=sizeof(struct sockaddr_in);
	if((bind(ssock,(struct sockaddr*)&client,len))==-1){
		perror("bind: ");
		exit(-1);
	}
	
	if((listen(ssock,5))==-1){
		perror("listen: ");
		exit(-1);
	}

	if((csock=accept(ssock,(struct sockaddr*)&client,&len))==-1){
		perror("accept: ");
		exit(-1);		
	}
	bool loggedIn = false;
	while(1){
		recv(csock,&input,sizeof(input),0);
		printf("input received: %s\n",input);
		if(!loggedIn){
			if(match(password,input)){
				loggedIn = true;
				bool flag = true;
				send(csock,&flag,sizeof(flag),0);
				
			}else{
				bool flag = false;
				send(csock,&flag,sizeof(flag),0);
			}
		}else{
			char i[100] = "Hi";
			if(match(input,i)){
				char res[100] = "Hello";
				send(csock,&res,sizeof(res),0);
			}else{
				char res[100] = "Invalid input!";
				send(csock,&res,sizeof(res),0);
			}
		}
		
		
	}
	
	close(ssock);
	
}
