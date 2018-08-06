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
int sock;      // client socket discriptor
int a,b,c,d,e,f,g,i;char q;
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

printf("enter student ID to find marks : \n");
scanf("%d",&a);
struct stud A;A.ID=a;
send(sock,&a,sizeof(a),0);  
recv(sock,&b,sizeof(b),0);	A.math=b;
recv(sock,&c,sizeof(b),0);	A.phys=c;
recv(sock,&d,sizeof(b),0);	A.bio=d;
recv(sock,&e,sizeof(b),0);	A.chem=e;
recv(sock,&f,sizeof(b),0);	A.eng=f;

printf("marks -- maths = %d physics = %d biology = %d chemistry = %d english = %d \n",b,c,d,e,f);
                           // receiving data from client
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
