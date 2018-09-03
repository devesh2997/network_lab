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

struct word{
	char word[100];
	char meaning[100];
};

void insert(struct word* dict[20], char w[100]){
	int i=0;
	while(dict[i]!=NULL)i++;
	if(i>=20)printf("Dictionary Full!\n");
	else {
		dict[i] = new struct word();
		dict[i]->word = w;
		dict[i]->meaning = "meaning";
	}
}

char[] find(struct word* dict[20], char w[100]){
	for(int i=0;i<20;i++){
		if(dict[i]!=NULL && match(dict[i]->word, w)){
			return dict[i]->meaning;
		}
	}
	insert(dict,w);
	return "WORD_INSERTED";
}



int main(){
	int ssock,csock;
	char word[100];
	unsigned int len;

	struct word* dict[20];
	int i =0;
	for(;i<15;i++){
		dict[i] = new struct word();
		dict[i]->word = "test";
		dict[i]->meaning = "meaning";
	}

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

	while(1){
		recv(csock,&word,sizeof(word),0);
		char meaning[] = find(dict,word);

		send(csock,&meaning,sizeof(meaning),0);
	}
	
	close(ssock);
	
}
