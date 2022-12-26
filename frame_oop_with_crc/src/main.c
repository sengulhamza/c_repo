#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "frame_oop_with_crc.h"

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