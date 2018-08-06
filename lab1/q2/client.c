#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>



int main(){
    int sock;      // client socket discriptor
    int a,c,i;
    unsigned int len;
    char ch[3]="no";
    char ch1[3];

    struct sockaddr_in client;
    if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){  // client socket is created..
        perror("socket: ");
        exit(-1);
    }

    client.sin_family=AF_INET;
    client.sin_port=htons(10000);        // initializing  socket  parameters 
    client.sin_addr.s_addr=INADDR_ANY;
    //inet_addr("127.0.0.1");
    bzero(&client.sin_zero,0); //appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.. 


    len=sizeof(struct sockaddr_in);
    if((connect(sock,(struct sockaddr *)&client,len))==-1){  //conneting to client
        perror("connect: ");
        exit(-1);
    }
    while(1){
        printf("enter a number:\n");
        scanf("%d",&a);

        send(sock,&a,sizeof(a),0);
        recv(sock,&c,sizeof(c),0);
        printf("required factorial is %d\n",c);
        printf("\ndo you want to exit...press 'no'\n");
        scanf("%s",ch1);
        //printf("%s\n",ch1);
        //printf("%s\n",ch);

        if((i=strcmp(ch,ch1))==0){
            close(sock);
            exit(0);
        }
    }
}
