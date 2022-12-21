#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define DEBUG 1               //Debug mode define

#if DEBUG
#define VARIABLE_PTR_STRGFY(var) var, #var
static void hex_dump(uint8_t *buffer, char *var_name, size_t len)
{
    printf("\r\n%s\r\n", var_name);
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
#endif

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

/**
 * Calculate the CRC of the payload
 * @param[in] payload
 * @param[in] length
 * @param[out] crc
 */
static uint16_t frame_oop_calculate_crc(uint8_t *payload, uint8_t length)
{
    uint16_t crc = 0xFFFF;
    uint8_t i;
    while (length--) {
        crc ^= *payload++;
        for (i = 0; i < 8; i++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0x8408;
            } else {
                crc = (crc >> 1);
            }
        }
    }
    return crc;
}

/**
 * Prepare frame
 * @param[in] command_frame_t *frame
 * @param[in] id
 * @param[in] *payload
 * @param[in] length
 * @param[out] returns frame length
 */
static uint16_t frame_oop_prepare_frame(command_frame_t *frame, uint8_t id, uint8_t *payload, uint8_t length)
{
    uint8_t *frame_payload_p = frame->payload;
    frame->length = length;
    frame->id = id;
    while (length--) {
        *frame_payload_p++ = *payload++;
    }
    frame->crc = frame_oop_calculate_crc(frame->payload, frame->length);
#ifdef DEBUG
    hex_dump(VARIABLE_PTR_STRGFY((uint8_t *)frame), sizeof(command_frame_t));
    hex_dump(VARIABLE_PTR_STRGFY(&frame->id), sizeof(frame->id));
    hex_dump(VARIABLE_PTR_STRGFY(&frame->length), sizeof(frame->length));
    hex_dump(VARIABLE_PTR_STRGFY(frame->payload), frame->length);
    hex_dump(VARIABLE_PTR_STRGFY((uint8_t *)&frame->crc), sizeof(frame->crc));
#endif
    return frame->length;
}

/**
 * Parse a command frame and verify the CRC
 * @param[in] command_frame_t *frame
 * @param[out] if CRC is valid return 1, else 0
 */
static uint8_t frame_oop_parse_command_frame(command_frame_t *frame)
{
    // Calculate the expected CRC
    uint16_t expected_crc = frame_oop_calculate_crc(frame->payload, frame->length);

    // Compare the expected CRC to the one in the frame
    return expected_crc != frame->crc ? 0 : 1;
}

/**
 * Send a command frame
 * @param[in] command_frame_t *frame
 * @param[out] if defined LOOPBACK, frame goes to parser (loopback) and return parser's return value.
 */
static uint8_t send_command_frame(command_frame_t *frame)
{
    // Calculate the CRC of the payload
    frame->crc = frame_oop_calculate_crc(frame->payload, frame->length);

    // TODO: Implement code to send the command frame. (TCP/IP, serial ...)
#ifdef LOOPBACK
    return frame_oop_parse_command_frame(frame);
#endif
    return 1;
}

int main()
{
    // Create a command frame
    command_frame_t test_frame = {0};

    // Prepare frame
    frame_oop_prepare_frame(&test_frame, FRAME_OOP_TEST_ID, (uint8_t *)FRAME_OOP_TEST_MSG, sizeof(FRAME_OOP_TEST_MSG));

    // Send the command frame
    uint8_t result = send_command_frame(&test_frame);
    if (result) {
        printf("Command frame sent successfully\n");
    } else {
        printf("Error sending command frame\n");
    }
    return 0;
}
