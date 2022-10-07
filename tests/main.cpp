#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL.h>

#include <fstream>
//#include <wtypes.h>

#include "OJDemo.h"
#include "FileHandler.h"
#include "Random.h"
#include "Debug.h"
#include "Jloader.h"

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
    Random::seed_random();

    // Clear the output log
    Debug::clear();

    nlohmann::json j_loader = Jloader::get("data/init.json");

    // int native_height = 0;
    // int native_width = 0;

    //GetDesktopResolution(native_width, native_height);

    int width = j_loader["width"];
    int height = j_loader["height"];
    int r = j_loader["r_value"];
    int g = j_loader["g_value"];
    int b = j_loader["b_value"];
    
    OJDemo demo = OJDemo("Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        width / 2, height / 2);  
    demo.start();

    return 0;
}
