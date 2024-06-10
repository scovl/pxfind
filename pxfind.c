#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

// Struct to hold the search result
typedef struct {
    int x;
    int y;
    int found;  // Use 0 for false, 1 for true
} PixelSearchResult;

// Function to get screen dimensions
void GetScreenDimensions(int *width, int *height) {
    *width = GetSystemMetrics(SM_CXSCREEN);
    *height = GetSystemMetrics(SM_CYSCREEN);
}

// Search for a pixel with the specified color within the given area
PixelSearchResult PixelSearch(int fovX, int fovY, int fovWidth, int fovHeight, COLORREF color, int variation) {
    HDC hdc = GetDC(NULL);
    if (!hdc) {
        fprintf(stderr, "Failed to get device context.\n");
        return (PixelSearchResult){0, 0, 0};
    }

    printf("Starting search...\n");
    fflush(stdout);
    printf("Target color: 0x%06lX\n", color);
    fflush(stdout);

    for (int y = fovY; y <= fovY + fovHeight; y++) {
        for (int x = fovX; x <= fovX + fovWidth; x++) {
            COLORREF pixelColor = GetPixel(hdc, x, y);
            if (abs(GetRValue(pixelColor) - GetRValue(color)) <= variation &&
                abs(GetGValue(pixelColor) - GetGValue(color)) <= variation &&
                abs(GetBValue(pixelColor) - GetBValue(color)) <= variation) {
                ReleaseDC(NULL, hdc);
                return (PixelSearchResult){x, y, 1};
            }
        }
    }

    ReleaseDC(NULL, hdc);
    return (PixelSearchResult){0, 0, 0};
}

int main() {
    int screenWidth, screenHeight;
    GetScreenDimensions(&screenWidth, &screenHeight);

    // Define the field of view (FOV) around the center of the screen
    int fovWidth = 800;  // Width of the FOV
    int fovHeight = 600; // Height of the FOV

    // Calculate the top-left coordinates of the FOV
    int fovX = (screenWidth - fovWidth) / 2;
    int fovY = (screenHeight - fovHeight) / 2;

    COLORREF targetColor = 0x00FF00; // Green in COLORREF format
    int colorVariation = 10;

    printf("Starting pxfind...\n");
    fflush(stdout);

    PixelSearchResult result = PixelSearch(fovX, fovY, fovWidth, fovHeight, targetColor, colorVariation);

    if (result.found) {
        printf("Pixel found at (%d, %d)\n", result.x, result.y);
    } else {
        printf("Pixel not found\n");
    }
    fflush(stdout);

    return 0;
}
