#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>

#include "TextureHandler.h"
#include "InputHandler.h"
#include "Debugger.h"

/**
 * @brief Demonstration of the engine's capabilities
 */
class Demo
{

private:

    static SDL_Window* window; // Instance of the SDL Window
    static InputHandler* input_handler; // Instance of the Input Handler

    TextureHandler* texture_handler; // Instance of the Texture Handler
    Debugger* debugger; // Instance of the Debugger

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

    /**
     * @brief Gets the usable fonts from a json file
     * 
     */
    void get_available_fonts();

    /**
     * @brief Gets the usable colors from a json file and loads new color 
     * classes into the texture handler
     * 
     * @param path Json file holding color names and their perspective values
     */
    void get_colors(const char* path);

public:

    static SDL_Renderer* renderer;
    static SDL_Event event;
    static bool running; // Determines whether the demo is running

    Demo();
    ~Demo();

    /**
     * @brief Initializes SDL and sets up the Game engine. Call 'start' to 
     * begin the execution loop after the engine has been initialized
     * 
     * @param title Name of the executable window
     * @param x X position of the window
     * @param y Y position of the window
     * @param width Width of the window
     * @param height Height of the window
     * @param fullscreen If the window should be fullscreen
     * @param r Red value of the renderer background
     * @param g Green value of the renderer background
     * @param b Blue value of the renderer background
     */
    void init(const char* title, int x, int y, int width, int height, 
        bool fullscreen, int r, int g, int b);
    
    /**
     * @brief Starts the engine. Init must be called before this point
     */
    void start();

    /**
     * @brief Main loop of the engine, updates and renders things to the 
     * screen.
     */
    void execution_loop();

    /**
     * @brief Called once per frame. Updates things that need updating
     */
    void update();

    /**
     * @brief Called once per frame. Handles all SDL Events 
     */
    void handle_events();

    /**
     * @brief Called once per frame. Iterates through the active keys in the 
     * input handler and handles them

     */
    void handle_keys();

    /**
     * @brief Called oncer per frame. Draws all things that need drawing
     */
    void draw_all();

    /**
     * @brief Stops the engine
     */
    void quit();
    

};