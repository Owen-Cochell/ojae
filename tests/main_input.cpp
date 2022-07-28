#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <iostream>
//#include <wtypes.h>

#include "Demo.h"
#include "FileHandler.h"

bool running = false;

// Get the horizontal and vertical screen sizes in pixel
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

void TestCallback(SDL_Event& event) {
    // Testing callback ...

    std::cout << "In testing callback ..." << std::endl;
    std::cout << "Event type: " << event.type << std::endl;

    return;
}

void ExitCallback(SDL_Event& event) {
    // Exit SDL

    SDL_Quit();
    running = false;
}

void PrintKey(SDL_Event& event) {
    // When we get a key...

    std::cout << "Got a key: " << event.key.keysym.sym << std::endl;
}

int main(int argc, char* argv[])
{
    int native_height = 0;
    int native_width = 0;

    //GetDesktopResolution(native_width, native_height);

    int width = native_width;
    int height = native_height;
    
    //Demo demo;

    // demo.init("Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
    //      width, height, false);
    // demo.start();

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = SDL_CreateWindow("Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 200, 200, false);
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 27, 27, 65, 255);
    }

    // Test the callback system:

    InputTemp inp;
    KeyCallbacks key;

    // Add the test callback...

    inp.add_callback(SDL_KEYDOWN, TestCallback);

    key.add_callback(SDLK_ESCAPE, ExitCallback);

    // Add recursive handler to collection:

    //inp.add_callback(SDL_KEYDOWN, std::bind(&KeyCallbacks::handle_event, &key, std::placeholders::_1));

    inp.add_callback_test(SDL_KEYDOWN, key, &KeyCallbacks::handle_event);

    // Finally, add exit function if we get exit key:

    // Loop forever:

    SDL_Event event;

    while (true) {

        while(SDL_PollEvent(&event)) {

            // Handle each event:

            //std::cout << "Before handling event: " << event.type << std::endl;

            inp.handle_event(event);
        }
    }

    return 0;
}
