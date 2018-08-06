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

    int ssock,csock;       // creating server and clinet socket discriptor
    int a,b;
    double add,sub,mul,divs;
    
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

        recv(csock,&a,sizeof(a),0);
        recv(csock,&b,sizeof(b),0);
        add = a+b;
        sub = a-b;
        mul = a*b;
        divs = a/b; 
        send(csock,&add,sizeof(add),0);            // sending data to client...	
        send(csock,&sub,sizeof(sub),0);
        send(csock,&mul,sizeof(mul),0);
        send(csock,&divs,sizeof(divs),0);
        printf("\nsent sum =: %f\n",sum);
        printf("\nsent difference =: %f\n",sub);
        printf("\nsent product =: %f\n",mul);
        printf("\nsent division =: %f\n",divs);

    }


    close(ssock);

}
