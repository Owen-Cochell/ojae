#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL.h>

#include "Demo.h"
#include "FileHandler.h"

int main(int argc, char* argv[])
{
    FileHandler file_handler;

    nlohmann::json j_loader = file_handler.get("data/Screen_Properties.json");

    int width = j_loader["Width"];
    int height = j_loader["Height"];
    bool fullscreen = j_loader["Fullscreen"];

    Demo demo;

    demo.init("Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        width, height, fullscreen);
    demo.start();

    return 0;
}
