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

void solve(char q[150], char *ans){
	FILE * fp; 
	fp = fopen("database.txt", "r");
	if (fp == NULL){
		printf("Error in reading file\n");
		return;
	}
	char ques[150];
	char a[150];
	while (fgets(ques, sizeof(ques), fp)) {
		fgets(a, sizeof(a), fp);
		printf("%s - %s",q,ques);
		int i = strcmp(q,ques);
		printf("%d\n",i);
        if(strcmp(q,ques)==0){
			printf("here\n");
			ans = a;
			return;
		}
    }
	printf("wtf\n");
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

	char q[150];
	while(1){
		recv(csock,&q,sizeof(q),0);

		char *ans;
		solve(q,ans);
		send(csock,&ans,sizeof(ans),0);
	}
}