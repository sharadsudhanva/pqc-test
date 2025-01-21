#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/select.h>


#include "tcp.h"
#include "pqc.h"

int tcp_client_connection_send(int sockfd, uint8_t* buf, unsigned int size){
		int n;
		printf("\nsockfd: %d & size: %u %d\n",sockfd,size,buf[2]);

		//send the message line to the server
		n = write(sockfd, buf, size);
		if (n < 0) {
			printf("Writing to socket failed.\n");
		}
		return n;
}


int tcp_send_public_key(int sockfd, uint8_t *p_key){
    uint8_t buf[20000] = INIT_TCP_COMMAND(SEND_PUB_KEY,sizeof(pubKey));
    struct TCP_COMMAND *cmd = (struct TCP_COMMAND *) buf;
    pubKey *args = (pubKey*) &buf[ sizeof(struct TCP_COMMAND) ];
    memcpy(args->pub_key,p_key,sizeof(pubKey));
    int i;
    printf("Sending public key to bob\n");
    return tcp_client_connection_send(sockfd, (uint8_t*)buf, sizeof(struct TCP_COMMAND) + TCP_COMMAND_ARGLEN(*cmd));
}

int tcp_send_encaps_shared_cipher(int sockfd, uint8_t *ciphertext){
    uint8_t buf[20000] = INIT_TCP_COMMAND(SEND_ENCAPS_CIPHER,sizeof(encapsCipher));
    struct TCP_COMMAND *cmd = (struct TCP_COMMAND *) buf;
    encapsCipher *args = (encapsCipher*) &buf[ sizeof(struct TCP_COMMAND) ];
    memcpy(args->ciphertext,ciphertext,OQS_KEM_kyber_768_length_ciphertext);
   

    int i;
    printf("Sending cipher text to Alice\n");
   
    return tcp_client_connection_send(sockfd, (uint8_t*)buf, sizeof(struct TCP_COMMAND) + TCP_COMMAND_ARGLEN(*cmd));
}


void tcp_server_command_parser(struct TCP_COMMAND recvcmd, int sockfd){
    uint16_t n;
	uint16_t offset = 0;
	uint64_t arglen = TCP_COMMAND_ARGLEN(recvcmd);
	uint8_t buf[20000];
    
    while((n = read(sockfd, (void*) &buf[offset], arglen - offset)) >= 0) {
		offset += n;
		if(offset == arglen) {
			printf("tcp_server_command_parser : Got valid command %x. args size %lu\n", recvcmd.cmd, arglen);
			break;
		}
	}

    switch(recvcmd.cmd) {
        
        case SEND_PUB_KEY:
        {
            pubKey *args = (pubKey *) buf;
            printf("Public Key Recvd\n");
            
            ENCAPS(args->pub_key);
            printf("Shared Secret Key:\n");
            int i;
            for(i=0;i< OQS_KEM_kyber_768_length_shared_secret; i++){
                printf("%d ",shared_secret_e[i]);
            }
            printf("\n");
            tcp_send_encaps_shared_cipher(sockfd,ciphertext);
            break;
        }
        case SEND_ENCAPS_CIPHER:
        {
            encapsCipher *args  = (encapsCipher *)buf;
            int i;
            printf("Encaps recieved\n");
            // for(i=0;i< OQS_KEM_kyber_768_length_shared_secret; i++){
            //     printf("%d ",args->shared_secret_e[i]);
            // }
            memcpy(ciphertext,args->ciphertext, OQS_KEM_kyber_768_length_ciphertext);
            DECAPS(ciphertext,secret_key);
            printf("Decaps Done\n");
            printf("Shared Secret Key:\n");
            for(i=0;i< OQS_KEM_kyber_768_length_shared_secret; i++){
                printf("%d ",shared_secret_d[i]);
            }
            printf("Done\n");
            break;
        }
        default:
        {
            printf("Invalid Command");
            break;
        }
    }
}