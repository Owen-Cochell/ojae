#include "OJAsciiEngine.h"
#include "Debug.h"
#include "nlohmann/json.hpp"
#include "Jloader.h"

#include <iostream>

// Constructors/Deconstructors

OJAsciiEngine::OJAsciiEngine(const char* title, int x, int y, int width,
    int height)
{
    running = false;
    
    // Initialize screen properties
    screen_width = width;
    screen_height = height;

    // If SDL fails to init
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        Debug::log("[ERR] SDL Failed to Init");
        exit(0);
    }

    // Create a window and renderer for SDL rendering
    window = SDL_CreateWindow(title, x, y, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 25, 25, 35, 255);

    // Create a TextureHandler
    texture_handler = new TextureHandler(renderer);

    nlohmann::json j_loader = Jloader::get("data/init.json");

    get_fonts("data/available_fonts.json");
    get_colors(static_cast<std::string>(j_loader["color_path"]).c_str());
}

OJAsciiEngine::~OJAsciiEngine() 
{
    delete texture_handler;
}

// Private Members

void OJAsciiEngine::get_fonts(const char* path)
{
    // If the file does not exist
    if(!Debug::file_exists(path))
    {
        Debug::log("[ERR] OJAsciiEngine.get_fonts -> Could not open file: ", 
            false, true);
        Debug::log(path, false, false);
        exit(0);
    }

    // Get the json object from the font file
    nlohmann::json j_loader = Jloader::get(path);

    // Iterate through the fonts in the json object and add them to the fonts
    for(nlohmann::json::iterator it = j_loader.begin(); it != j_loader.end();
        it++)
    {
        Debug::log("[OUT] Getting font: ", false, true);
        Debug::log(it.key(), true, false);
        fonts[it.key()] = it.value();
    }

    // There are no fonts to use
    if(fonts.size() == 0)
    {
        Debug::log("[ERR] No fonts were found");
        exit(0);
    }
}

void OJAsciiEngine::get_colors(const char* path)
{
    // If the file does not exist
    if(!Debug::file_exists(path))
    {
        Debug::log("[ERR] OJAsciiEngine.get_colors -> Could not open file: ",
            false, true);
        Debug::log(path, false, false);
        exit(0);
    }

    // Get the json object from the colors file
    nlohmann::json j_loader = Jloader::get(path);

    // Iterate through the colors in the json object and add them to the 
    // TextureHandler
    for(nlohmann::json::iterator it = j_loader.begin(); it != j_loader.end();
        it++)
    {
        Debug::log("[OUT] Loading Color: ", false, true);
        Debug::log(std::string(it.key()), true, false);

        texture_handler->add_color(new Color(it.key(), it.value()[0], 
            it.value()[1], it.value()[2]));
    }
}

// Public Members

void OJAsciiEngine::start_OJAE() 
{
    running = true;
    execution_loop();
}

void OJAsciiEngine::execution_loop()
{
    while(running)
    {
        frame_start = SDL_GetTicks64();

        update();
        handle_events();
        draw();

        frame_time = SDL_GetTicks64() - frame_start;

        if(FRAME_DELAY > frame_time)
        {
            SDL_Delay(FRAME_DELAY - frame_time);
        }
    }    

    quit();
}

void OJAsciiEngine::update() {}

void OJAsciiEngine::handle_events() {}

void OJAsciiEngine::clear_screen()
{
    SDL_RenderClear(renderer);
}

void OJAsciiEngine::draw() {}

void OJAsciiEngine::render()
{
    SDL_RenderPresent(renderer);
}

void OJAsciiEngine::quit() 
{
    SDL_Quit();
}
