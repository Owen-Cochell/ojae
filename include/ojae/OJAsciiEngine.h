#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include <string>

#include "TextureHandler.h"

class OJAsciiEngine
{

protected:

    SDL_Window* window; // Instance of the SDL Window

    SDL_Renderer* renderer; // Instance of the renderer
    SDL_Event event; // Instance of the SDL Event
    
    bool running; // If the engine is simulating

    const int TARG_FPS = 60; // Target frames per second

    /**
     * @brief Milisecond delay between each frame to acquire target fps
     */
    const int FRAME_DELAY = 1000 / TARG_FPS;

    Uint64 frame_start; // TIme stamp of when the current frame started
    int frame_time; // Amount of time the last frame took

    int screen_width; // Width of the screen
    int screen_height; // Height of the screen

    /**
     * @brief Font names to their specified font paths
     * 
     */
    std::unordered_map<std::string, std::string> fonts;

    TextureHandler* texture_handler; // Instance of the Texture Handler

    /**
     * @brief Loads available fonts into the engine
     * 
     * @param path Path to the available font file
     */
    void get_fonts(const char* path);
    
    /**
     * @brief Loads available colors into the TextureHandler
     * 
     * @param path Path to the available colors file
     */
    void get_colors(const char* path);

public:

    /**
     * @brief OJAsciiEngine Constructor
     * 
     * @param title Title of the Window
     * @param x X position of the window
     * @param y Y position of the window
     * @param width Width of the window
     * @param height Height of the window
     */
    OJAsciiEngine(const char* title, int x, int y, int width, int height);
    virtual ~OJAsciiEngine();

    void start_OJAE();
    void execution_loop();
    virtual void update();
    virtual void handle_events();
    void clear_screen();
    virtual void draw();
    void render();
    void quit();
};
