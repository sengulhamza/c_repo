#include <stdint.h>
#include <stdio.h>
#include <string.h>

void hex_dump(uint8_t *buffer, char *var_name, size_t len)
{
    printf("\r\n%s - length:%zu\r\n", var_name, len);
    printf("HEX\t\t\t\t\t\t   ASCII\n");
    printf("---\t\t\t\t\t\t   -----\n");
    for (int i = 0; i < len; i++) {
        printf("%02x ", buffer[i]);
        if ((i + 1) % 8 == 0) {
            printf(" ");
        } \
        if ((i + 1) % 16 == 0) {
            printf(" ");
            for (int j = i - 15; j <= i; j++) {
                printf("%c", buffer[j]);
            }
            printf("\n");
        }
    }
    if (len % 16 != 0) {
        int remaining = len % 16;
        for (int i = 0; i < 16 - remaining; i++) {
            printf("   ");
            if ((i + 1 + len - remaining) % 8 == 0) {
                printf(" ");
            }
        }
        printf("  ");
        for (int i = len - remaining; i < len; i++) {
            printf("%c", buffer[i]);
        } \
        printf("\n");
    }
}
