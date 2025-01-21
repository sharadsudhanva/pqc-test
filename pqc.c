#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/select.h>

//PQC liboqs.
#include<oqs/oqs.h>
#include "pqc.h"

uint8_t public_key[OQS_KEM_kyber_768_length_public_key];
uint8_t secret_key[OQS_KEM_kyber_768_length_secret_key];
uint8_t ciphertext[OQS_KEM_kyber_768_length_ciphertext];
uint8_t shared_secret_e[OQS_KEM_kyber_768_length_shared_secret];
uint8_t shared_secret_d[OQS_KEM_kyber_768_length_shared_secret];

OQS_STATUS generatePQC(){
        int i;
        OQS_STATUS rc = OQS_KEM_kyber_768_keypair(public_key, secret_key);
        if (rc != OQS_SUCCESS) {
		printf("ERROR: OQS_KEM_kyber_768_keypair failed!\n");
		return OQS_ERROR;
	    }
        printf("Public Key:\n");
        for(i=0 ; i < OQS_KEM_kyber_768_length_public_key; i++){
                printf("%d ", public_key[i]);
        }
        // printf("PrivateKey: \n");
        // for(i=0 ; i < OQS_KEM_kyber_768_length_secret_key; i++){
        //         printf("%d ", secret_key[i]);
        // }
	return OQS_SUCCESS;
}   


OQS_STATUS ENCAPS(uint8_t *public_key){

    OQS_STATUS rc = OQS_KEM_kyber_768_encaps(ciphertext, shared_secret_e, public_key);
    if (rc != OQS_SUCCESS) {
    printf("ERROR: OQS_KEM_kyber_768_keypair failed!\n");
        return OQS_ERROR;
    }
    return OQS_SUCCESS;
}

OQS_STATUS DECAPS(uint8_t *ciphertext, uint8_t *secret_key){
    int i;
    OQS_STATUS rc = OQS_KEM_kyber_768_decaps(shared_secret_d, ciphertext, secret_key);
    printf("DECAPS \n");
    if (rc != OQS_SUCCESS) {
    printf("ERROR: OQS_KEM_kyber_768_keypair failed!\n");
        return OQS_ERROR;
    }
    // for(i=0;i< OQS_KEM_kyber_768_length_shared_secret; i++){
    //             printf("%d ",shared_secret_d[i]);
    //         }
    // printf("\n");
    return OQS_SUCCESS;
}
