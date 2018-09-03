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

char* words[20];

int main(){

	words[0] = "test";
	words[1] = "test1";
	words[2] = "test2";
	words[3] = "test3";
	words[4] = "test4";
	words[5] = "test5";
	words[6] = "test6";
	words[7] = "test7";
	words[8] = "test8";

	int sock;
	char word[100];
	char meaning[100];
	unsigned int len;
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

	while(1){
		printf("Enter the word to search : ");
		scanf("%s",word);
		send(sock,&word,sizeof(word),0);
		recv(sock,&meaning,sizeof(meaning),0);
		printf("Meaning of %s is %s ",word,meaning);
	}
}
