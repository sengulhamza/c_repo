#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "frame_oop_with_crc.h"

#define DEBUG 1               //Debug mode define

#if DEBUG
#include "hex_dump.h"
#endif
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
uint16_t frame_oop_prepare_frame(command_frame_t *frame, uint8_t id, uint8_t *payload, uint8_t length)
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
uint8_t send_command_frame(command_frame_t *frame)
{
    // Calculate the CRC of the payload
    frame->crc = frame_oop_calculate_crc(frame->payload, frame->length);

    // TODO: Implement code to send the command frame. (TCP/IP, serial ...)
#ifdef LOOPBACK
    return frame_oop_parse_command_frame(frame);
#endif
    return 1;
}

