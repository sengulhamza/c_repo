#ifndef _FRAME_OOP_WITH_CRC_H_
#define _FRAME_OOP_WITH_CRC_H_

#define LOOPBACK              //Loopback test define

#define FRAME_OOP_TEST_MSG    "https://meplis.dev"
#define FRAME_OOP_TEST_ID     (0xC2)
#define FRAME_OOP_PAYLOAD_LEN (256) //If needs increase, check crc algorithm

/**
 * Struct for storing command frame data
 */
typedef struct {
    uint8_t id;
    uint8_t length;
    uint8_t payload[FRAME_OOP_PAYLOAD_LEN];
    uint16_t crc;
} command_frame_t;

#ifdef __cplusplus
extern "C" {
#endif

uint16_t frame_oop_prepare_frame(command_frame_t *frame, uint8_t id, uint8_t *payload, uint8_t length);
uint8_t send_command_frame(command_frame_t *frame);

#ifdef __cplusplus
}
#endif

#endif