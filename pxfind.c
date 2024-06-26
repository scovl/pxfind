#include "pxfind.h"
#include <stdio.h>
#include <stdlib.h>

// Function to get screen dimensions
void GetScreenDimensions(int *width, int *height) {
    *width = GetSystemMetrics(SM_CXSCREEN);
    *height = GetSystemMetrics(SM_CYSCREEN);
}

// Function to calculate the FOV centered on the screen
FieldOfView CalculateFOV(int screenWidth, int screenHeight, int fovWidth, int fovHeight) {
    FieldOfView fov;
    fov.x = (screenWidth - fovWidth) / 2;
    fov.y = (screenHeight - fovHeight) / 2;
    fov.width = fovWidth;
    fov.height = fovHeight;
    return fov;
}

// Search for a pixel with the specified color within the given area
PixelSearchResult PixelSearch(FieldOfView fov, COLORREF color, int variation) {
    HDC hdc = GetDC(NULL);
    if (!hdc) {
        fprintf(stderr, "Failed to get device context.\n");
        exit(EXIT_FAILURE);  // Terminate the program since it's a critical error
    }

    printf("Starting search...\n");
    printf("Target color: 0x%06lX\n", color);

    for (int y = fov.y; y <= fov.y + fov.height; y++) {
        for (int x = fov.x; x <= fov.x + fov.width; x++) {
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

    int fovWidth = 800;
    int fovHeight = 600;
    FieldOfView fov = CalculateFOV(screenWidth, screenHeight, fovWidth, fovHeight);

    COLORREF targetColor = 0x00FF00;  // Green in COLORREF format
    int colorVariation = 10;

    printf("Starting pxfind...\n");

    PixelSearchResult result = PixelSearch(fov, targetColor, colorVariation);

    if (result.found) {
        printf("Pixel found at (%d, %d)\n", result.x, result.y);
    } else {
        printf("Pixel not found\n");
    }

    return 0;
}
