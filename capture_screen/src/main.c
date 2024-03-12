#include <stdio.h>
#include <stdlib.h>
#include <ApplicationServices/ApplicationServices.h>

void CaptureScreen(const char *outputFileName)
{
    // Get the main screen dimensions
    CGRect screenBounds = CGDisplayBounds(CGMainDisplayID());
    int screenWidth = (int)CGRectGetWidth(screenBounds);
    int screenHeight = (int)CGRectGetHeight(screenBounds);

    // Create a bitmap context for the screenshot
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef context = CGBitmapContextCreate(NULL, screenWidth, screenHeight, 8, screenWidth * 4, colorSpace, kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Little);

    // Capture the screen into the bitmap context
    CGImageRef screenshot = CGDisplayCreateImage(CGMainDisplayID());
    CGContextDrawImage(context, screenBounds, screenshot);
    CGImageRelease(screenshot);

    // Get the bitmap data
    unsigned char *pixels = CGBitmapContextGetData(context);
    printf("RES: %d x %d\r\n", screenWidth, screenHeight);

    // Iterate through the pixel data and print RGB values to the console
    for (int y = 1331; y < screenHeight; ++y) {
        for (int x = 0; x < screenWidth; ++x) {
            // Calculate the index of the current pixel in the pixel array
            int index = y * screenWidth * 4 + x * 4;

            // Extract RGB values
            unsigned char red = pixels[index + 2];
            unsigned char green = pixels[index + 1];
            unsigned char blue = pixels[index];

            if (1) {
                // Print RGB values to the console
                printf("Pixel at (%d, %d): R=%u, G=%u, B=%u\n", x, y, red, green, blue);
            }
        }
    }

    // Save or process the pixel data as needed
    // Example: Save to a file
    FILE *outputFile = fopen(outputFileName, "wb");
    if (outputFile != NULL) {
        fwrite(pixels, 1, screenWidth * screenHeight * 4, outputFile);
        fclose(outputFile);
    }

    // Cleanup
    CGContextRelease(context);
    CGColorSpaceRelease(colorSpace);
}

int main()
{
    CaptureScreen("screenshot.bmp");
    return 0;
}
