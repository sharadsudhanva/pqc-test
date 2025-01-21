#ifndef PQC_H
#define PQC_H

#include<oqs/oqs.h>

extern uint8_t public_key[OQS_KEM_kyber_768_length_public_key];
extern uint8_t secret_key[OQS_KEM_kyber_768_length_secret_key];
extern uint8_t ciphertext[OQS_KEM_kyber_768_length_ciphertext];
extern uint8_t shared_secret_e[OQS_KEM_kyber_768_length_shared_secret];
extern uint8_t shared_secret_d[OQS_KEM_kyber_768_length_shared_secret];


OQS_STATUS generatePQC();
OQS_STATUS ENCAPS(uint8_t *public_key);
OQS_STATUS DECAPS(uint8_t *ciphertext, uint8_t *secret_key);

#endif