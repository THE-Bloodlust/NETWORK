#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main(){
char buffer[1024] = {0};
char msg[1024] = {0};
struct sockaddr_in client;
client.sin_addr.s_addr = inet_addr("127.0.0.1");
client.sin_port = htons(1000);
client.sin_family=AF_INET;
printf("=======================CLIENT SIDE=====================");
// SOCKET CREATION
int sockfd = socket(AF_INET, SOCK_STREAM,0);
if(sockfd<0){
perror("\nSOCKET CREATION FAILED.");
}
//CONNECTING TO SERVER
int connfd = connect(sockfd, (struct sockaddr *)&client, sizeof(client));
if(connfd<0){
perror("\nCOULD NOT CONNECT.");
}
//SENDING MESSAGES TO SERVER
while(1){
    printf("\nSEND DATA TO SERVER:");
    fgets((char *)msg,1024, stdin);
    if(strcmp(msg,"exit\n") == 0){
        break;
    }
int sendfd = send(sockfd,msg, strlen(msg), 0);
   if(strcmp(msg,"exit\n")==0){
        break;
    }
if(sendfd < 0){
perror("\nCOULDNOT SEND MESSAGE");
}
//CLEARS THE BUFFER
memset(buffer,0,sizeof(buffer));

//RECIEVING SERVERS MESSAGE
int recfd = recv(sockfd,buffer, sizeof(buffer)-1,0);
if(recfd <= 0){
perror("\nCOULD NOT RECIEVE MESSAGE.");
}
printf("SERVER SAYS:%s",buffer);
}
close(sockfd);
return 0;
}
