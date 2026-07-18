#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(){
char msg[1024] = {0};
char buffer[1024] = {0};
int port= 1000;
struct sockaddr_in target;
target.sin_family=AF_INET;
target.sin_port=htons(port);
target.sin_addr.s_addr=inet_addr("127.0.0.1");
socklen_t target_len =sizeof(target);
printf("========================SERVER SIDE=======================");
//CREATING A SOCKET
int sockfd = socket(AF_INET,SOCK_STREAM,0);
if(sockfd < 0){
perror("\nCOULD NOT CREATE SOCKET.");
}
//BINDING THE ADDRESS 
int bindfd = bind(sockfd,(struct sockaddr*)&target, sizeof(target));
if(bindfd < 0){
perror("\nBINDING FAILED.");
}
//LISTENING
int listfd = listen(sockfd, 5);
if(listfd <  0 ){
printf("\n COULD NOT LISTEN.");
        }
//ACCEPTING CLIENT CONNECTION
int accfd = accept(sockfd, (struct sockaddr*)&target, &target_len);
if(accfd<0){
perror("\nCOULD NOT ACCEPT CONNECTION");
}
else{
printf("\nCONNECTED.");
}
//RECIEVING DATA
while(1){
    memset(msg,0,sizeof(msg));
int recfd = recv(accfd, buffer, sizeof(buffer)-1, 0);
if(recfd <= 0){
perror("DIDNOT RECIEVE MESSAGE OR THE CLIENT DISCONNECTED.");
}
if(strcmp(buffer,"exit\n") == 0){
        break;
    }
buffer[recfd]='\0';
printf("\nCLIENT SAYS:%s",(char*)buffer);
printf("Enter reply: ");
fgets(msg,sizeof(msg),stdin);
if(strcmp(msg,"exit\n")==0){
        break;
    }
//SENDING DATA TO CLIENT
int sendfd= send(accfd, msg, strlen(msg),0);
if(sendfd<0){
perror("\nCOULD NOT SEND DATA.");
}}
close(sockfd);
return 0;
}
