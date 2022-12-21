#ifndef _AUTH_WITH_CMAC_H_
#define _AUTH_WITH_CMAC_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int auth_cmac_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext);
int auth_cmac_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext);

#ifdef __cplusplus
}
#endif

#endif