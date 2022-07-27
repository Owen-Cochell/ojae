#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <wtypes.h>

#include "Demo.h"
#include "FileHandler.h"

// Get the horizontal and vertical screen sizes in pixel
void GetDesktopResolution(int& horizontal, int& vertical)
{
   RECT desktop;
   // Get a handle to the desktop window
   const HWND hDesktop = GetDesktopWindow();
   // Get the size of screen to the variable desktop
   GetWindowRect(hDesktop, &desktop);
   // The top left corner will have coordinates (0,0)
   // and the bottom right corner will have coordinates
   // (horizontal, vertical)
   horizontal = desktop.right;
   vertical = desktop.bottom;
}

int main(int argc, char* argv[])
{
    int native_height = 0;
    int native_width = 0;

    GetDesktopResolution(native_width, native_height);

    int width = native_width;
    int height = native_height;
    
    Demo demo;

    demo.init("Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        width, height, false);
    demo.start();

    return 0;
}
