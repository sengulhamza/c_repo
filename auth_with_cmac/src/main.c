#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "hex_dump.h"
#include "auth_with_cmac.h"

int main()
{
    /* A 256 bit key */
    unsigned char *key = (unsigned char *)"01234567890123456789012345678901";

    /* A 128 bit IV */
    unsigned char *iv = (unsigned char *)"0123456789012345";

    /* Message to be encrypted */
    unsigned char *plaintext = (unsigned char *)"The quick brown fox jumps over the lazy dog";

    /*
     * Buffer for ciphertext. Ensure the buffer is long enough for the
     * ciphertext which may be longer than the plaintext, depending on the
     * algorithm and mode.
     */
    unsigned char ciphertext[128];

    /* Buffer for the decrypted text */
    unsigned char decryptedtext[128];

    /* Encrypt the plaintext */
    int ciphertext_len = auth_cmac_encrypt(plaintext, strlen((char *)plaintext), key, iv, ciphertext);

    /* Do something useful with the ciphertext here */
    hex_dump(VARIABLE_PTR_STRGFY((uint8_t *) ciphertext), ciphertext_len);
    /* Decrypt the ciphertext */
    int decryptedtext_len = auth_cmac_decrypt(ciphertext, ciphertext_len, key, iv, decryptedtext);

    /* Add a NULL terminator. We are expecting printable text */
    decryptedtext[decryptedtext_len] = '\0';

    /* Show the decrypted text */
    hex_dump(VARIABLE_PTR_STRGFY((uint8_t *) decryptedtext), decryptedtext_len);

    return 0;
}