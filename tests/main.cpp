#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
//#include <wtypes.h>

#include "Demo.h"
#include "FileHandler.h"

static std::fstream file_stream;

// // Get the horizontal and vertical screen sizes in pixel
// void GetDesktopResolution(int& horizontal, int& vertical)
// {
//    RECT desktop;
//    // Get a handle to the desktop window
//    const HWND hDesktop = GetDesktopWindow();
//    // Get the size of screen to the variable desktop
//    GetWindowRect(hDesktop, &desktop);
//    // The top left corner will have coordinates (0,0)
//    // and the bottom right corner will have coordinates
//    // (horizontal, vertical)
//    horizontal = desktop.right;
//    vertical = desktop.bottom;
// }

int main(int argc, char* argv[])
{
    // Clear the output log
    file_stream.open("OutputLog.txt", std::ios::out);
    file_stream.close();

    int native_height = 1080;
    int native_width = 1920;

    //GetDesktopResolution(native_width, native_height);

    int width = native_width;
    int height = native_height;
    
    Demo demo;

    demo.init("Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        width, height, false);
    demo.start();

    return 0;
}
