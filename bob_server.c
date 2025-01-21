#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/select.h>

//PQC liboqs.
#include<oqs/oqs.h>

#include "tcp.h"

#define PORT 8080



int main(){
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    int optval, valread;
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
	optval =1;
    struct TCP_COMMAND cmd;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void*) &optval, 2);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))< 0)
    {
            error("Binding failed");
    }
    printf("Binded \n");
    if (listen(sockfd, 3) < 0) {
            perror("listen failed");
    } else {
            printf("socket is listening\n");
    }
    clilen = sizeof(cli_addr);
    int confd = accept(sockfd, (struct sockaddr*)&cli_addr, (socklen_t*)&cli_addr);
    if(confd < 0){
        printf("Error in connecting\n");
    }
    else{
        printf("Connection Accepted\n");
    }
    while(1){
        uint8_t *buffer = (uint8_t*) &cmd;
        bzero((void*)&cmd, sizeof(cmd));
        if ((valread = read(confd, buffer, sizeof(struct TCP_COMMAND))) == 0){
            printf("Alice Disconnected.");
            break;
        }
        else{
                printf("Received message from Alice.");
                tcp_server_command_parser(cmd,confd);
          
        }
    }
    close(confd);
    
    return 0;
}
