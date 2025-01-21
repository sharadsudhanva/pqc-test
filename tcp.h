#ifndef TCP_H
#define TCP_H

#include<oqs/oqs.h>

#define SEND_PUB_KEY    0x11
#define SEND_ENCAPS_CIPHER  0x12

#define INIT_TCP_COMMAND(cmd, arglen)		{ (cmd), \
											(arglen) & 0xff, \
											((arglen) >> 8) & 0xff, \
                                            ((arglen) >> 16) & 0xff, \
                                            ((arglen) >> 64) & 0xff, \
                                            }

#define TCP_COMMAND_ARGLEN(tcpcmd)			( (tcpcmd).arglen0 | ((tcpcmd).arglen1 <<8) | ((tcpcmd).arglen2<< 16) | ((tcpcmd).arglen3 << 64))

struct TCP_COMMAND { 
	uint8_t cmd;
	uint8_t arglen0;
    uint8_t arglen1;
    uint8_t arglen2;
    uint8_t arglen3;

};

struct pubKey{
    uint8_t pub_key[OQS_KEM_kyber_768_length_public_key];

}typedef pubKey;


struct encapsCipher{
    uint8_t ciphertext[OQS_KEM_kyber_768_length_ciphertext];
    
}typedef encapsCipher;

int tcp_send_public_key(int sockfd, uint8_t *p_key);
void tcp_server_command_parser(struct TCP_COMMAND recvcmd, int sockfd);
int tcp_send_encaps_shared_cipher(int sockfd, uint8_t *ciphertext); 

#endif 