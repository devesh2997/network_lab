#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

struct stud{
	int math,phys,chem,bio,eng;
	int ID;

};
int main(){

int ssock,csock;       // creating server and clinet socket discriptor
int a,i;
char b,c;
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
struct stud ar[10];
for(int i=0;i<10;i++)
{ar[i].math=i;ar[i].phys=i*i;ar[i].bio=3*i;ar[i].chem=i*i+i/2;ar[i].eng=i+30;}
while(1){
	struct	stud A;	
	recv(csock,&A.ID,sizeof(A.ID),0);
	
	send(csock,&ar[A.ID].math,sizeof(ar[A.ID].math),0);            // sending data to client...
	send(csock,&ar[A.ID].phys,sizeof(ar[A.ID].math),0); 
	send(csock,&ar[A.ID].bio,sizeof(ar[A.ID].math),0); 
	send(csock,&ar[A.ID].chem,sizeof(ar[A.ID].math),0); 
	send(csock,&ar[A.ID].eng,sizeof(ar[A.ID].math),0); 	
	printf("marks for ID no. %d sent\n",A.ID);

}


close(ssock);









}
