#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

// Struct to hold the search result
typedef struct {
    int x;
    int y;
    int found;  // Use 0 for false, 1 for true
} PixelSearchResult;

// Search for a pixel with the specified color within the given area
PixelSearchResult PixelSearch(int left, int top, int right, int bottom, COLORREF color, int variation) {
    HDC hdc = GetDC(NULL);
    if (!hdc) {
        fprintf(stderr, "Failed to get device context.\n");
        return (PixelSearchResult){0, 0, 0};
    }

    for (int y = top; y <= bottom; y++) {
        for (int x = left; x <= right; x++) {
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
    int left = 0;
    int top = 0;
    int right = 1920;
    int bottom = 1080;
    COLORREF color = 0x00FF00; // Green in COLORREF format
    int variation = 10;

    PixelSearchResult result = PixelSearch(left, top, right, bottom, color, variation);

    if (result.found) {
        printf("Pixel found at (%d, %d)\n", result.x, result.y);
    } else {
        printf("Pixel not found\n");
    }

    return 0;
}
