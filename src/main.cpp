#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char* argv[])
{
    const int TARG_FPS = 60; // How many frames per second we want 
    const int FRAME_DELAY = 1000 / TARG_FPS; // Miliseconds delay between each frame to 
        // aquire target fps
    
    Uint32 frame_start; // Resembles the time stamp of the beginning of each frame
    int frame_time; // Measures the amount of time each frame took to execute

    return 0;
}