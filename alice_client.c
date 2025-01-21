
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/select.h>

#include<oqs/oqs.h>
#include "tcp.h"
#include "pqc.h"

#define PORT 8080


int main(int argc, char *argv[])
{
        int sockfd, portno, n , optval = 1;
        struct sockaddr_in serv_addr, client;
        struct in_addr server;
        // struct hostent *server;
        struct TCP_COMMAND cmd;
        int valread;
      
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd < 0){
                error("Error opening socket");
        }
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void*) &optval, 2);
        bzero((char *)&client,sizeof(client));
        client.sin_family = AF_INET;
        client.sin_port = 8000;
        inet_pton(AF_INET, "127.0.0.1",&client.sin_addr);
        if(bind(sockfd, (struct sockaddr *) &client, sizeof(client))< 0)
        {
                error("Binding failed");
        }
	#printf("Binded \n");
	
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        // inet_pton(AF_INET, argv[1],&serv_addr.sin_addr);
        inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
        //bcopy((char *) server->h_addr, (char *) &serv_addr, server->h_length);
        serv_addr.sin_port = htons(PORT);
	
	
        if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))< 0)
                error("Connection failed");

        OQS_STATUS rc = generatePQC();
        tcp_send_public_key(sockfd, public_key);       
        while(1){
                uint8_t *buffer = (uint8_t*) &cmd;
                bzero((void*)&cmd, sizeof(cmd));
                if ((valread = read(sockfd, buffer, sizeof(struct TCP_COMMAND))) == 0){
                        printf("Alice Disconnected.");
                        break;
                }
                else{
                        printf("Received message from Bob.");
                        tcp_server_command_parser(cmd,sockfd);
                }
        }     
        
        close(sockfd);
    
return 0;
}
