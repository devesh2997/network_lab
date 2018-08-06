#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

char* matchPassword(char *pass, int n){
    char validpass[] =  "testpassword";
    for(int i=0;i<n;i++){
        if(pass[i]!=validpass[i])return false;
    }
    return true;
}


int main(){

    int ssock,csock;       // creating server and clinet socket discriptor
    char pass[50];
    char res[50];
    bool c;
    int count;
    unsigned int len;

    struct sockaddr_in server,client;   // creating server & client socket object

    if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1){
        perror("socket: is not created");
        exit(-1);
    }

    server.sin_family=AF_INET;
    server.sin_port=htons(10000);       // initializing server socket parameters..
    server.sin_addr.s_addr=INADDR_ANY;
    //inet_addr("127.0.0.1");
    bzero(&server.sin_zero,0); //appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.. 


    len=sizeof(struct sockaddr_in);

    if((bind(ssock,(struct sockaddr *)&server,len))==-1){  // binding port & IP  
        perror("bind: ");
        exit(-1);
    }

    if((listen(ssock,5))==-1){     // listening for client
        perror("listen: ");                     
        exit(-1);
    }


    if((csock=accept(ssock,(struct sockaddr *)&client,&len))==-1){  // accepting connectn
        perror("accept: ");                         
        exit(-1);
    }
    while(1){

        recv(csock,pass,sizeof(pass),0);
        recv(csock,&count,sizeof(count),0);
        c=matchPassword(pass,count); 
        send(csock,&c,sizeof(c),0);            // sending data to client...	
        printf("\nauth status sent =: %d\n",c);
        char mesg[50];
        recv(csock,mesg,sizeof(mesg),0);
        printf("\nmessge received =: %s\n",mesg);
        char resmesg[50] = "Hello";
        send(csock,resmesg,sizeof(resmesg),0); 
        printf("\nmessge sent =: %s\n",resmesg);
    }


    close(ssock);

}
