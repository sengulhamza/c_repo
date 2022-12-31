#ifndef _TCP_MSG_H_
#define _TCP_MSG_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TCP_MSG_PAYLOAD_SIZE    64

typedef struct tcp_msg_t {
    uint8_t msg_id;
    uint8_t payload[TCP_MSG_PAYLOAD_SIZE];
    uint16_t len;
} tcp_msg_t;

#ifdef __cplusplus
}
#endif

#endif
