#ifndef PXFIND_H
#define PXFIND_H

#include <windows.h>

// Define the structure to hold the search result
typedef struct {
    int x;
    int y;
    int found;  // Use 0 for false, 1 for true
} PixelSearchResult;

// Define the structure for the Field of View (FOV)
typedef struct {
    int x;
    int y;
    int width;
    int height;
} FieldOfView;

// Function to get screen dimensions
void GetScreenDimensions(int *width, int *height);

// Function to calculate the FOV centered on the screen
FieldOfView CalculateFOV(int screenWidth, int screenHeight, int fovWidth, int fovHeight);

// Search for a pixel with the specified color within the given area
PixelSearchResult PixelSearch(FieldOfView fov, COLORREF color, int variation);

#endif // PXFIND_H
