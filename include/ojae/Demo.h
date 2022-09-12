#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>

#include "TextureHandler.h"
#include "InputHandler.h"
#include "Debugger.h"

class Demo
{

private:

    static SDL_Window* window;
    static InputHandler* input_handler;

    TextureHandler* texture_handler;
    Debugger* debugger;

    /**
     * @brief Path to available font files
     */
    std::map<std::string, std::string> font_paths; // Paths to the available fonts 
    std::vector<std::string> available_fonts; // Fonts that are available

    const int TARG_FPS = 60; // How many frames per second we want 
    const int FRAME_DELAY = 1000 / TARG_FPS; // Miliseconds delay between each frame to 
        // acquire target fps
    
    Uint32 frame_start; // Resembles the time stamp of the beginning of each frame
    int frame_time; // Measures the amount of time each frame took to execute

    int font_index ; // Index of the available fonts that is currently selected

    int screen_width; // Width of the screen
    int screen_height; // Height of the screen
    int standard_input_delay; // Standard delay for generic key input

    nlohmann::json j_loader; // Json file handler

    void get_available_fonts();

public:

    static SDL_Renderer* renderer;
    static SDL_Event event;
    static bool running; // Determines whether the demo is running

    Demo();
    ~Demo();

    void init(const char* title, int x, int y, int width, int height, 
        bool fullscreen, int r, int g, int b);
    void start();
    void execution_loop();
    void update();
    void handle_events();
    void handle_keys();
    void draw_all();
    void quit();
    

};