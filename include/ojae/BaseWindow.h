#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <map>

#include "TextRenderer.h"
#include "TextureHandler.h"

/**
 * @brief Controls the output of text and textures to a set size of the 
 * screen */
class BaseWindow
{

protected:

    SDL_Rect border_src;

    SDL_Rect top_border;
    SDL_Rect right_border;
    SDL_Rect bottom_border;
    SDL_Rect left_border;

    SDL_Texture* border;
    SDL_Texture* border_selected;

    TextRenderer* text_renderer; // Instance of the TextRenderer
    SDL_Texture* font_texture; // Texture for the active font

    const char* path; // Path to the font png

    TextureHandler* texture_handler; // Instance of the TextureHandler
    Debugger* debugger; // Instance of the Debugger

    int border_size; // Size of the border of the windows

    int start_x; // X Coordinate where the window begins
    int end_x; // X Coordinate where the window begins
    int start_y; // Y Coordinate where the window begins
    int end_y; // Y Coordinate where the window begins 

    bool taking_input; // Whether this info should handle keys from the input handler


public:

    BaseWindow();
    BaseWindow(TextureHandler* _texture_handler, Debugger* _debugger, 
        int start_x, int end_x, int start_y, int end_y, bool taking_input);
    ~BaseWindow();

    std::string get_font_path();

    /**
     * @brief Loads a new font into the TilemapWindow's TextRenderer
     * 
     * @param new_path Path to the new json font file
    */
    void load_font(const char* new_path);

    virtual void update();
    virtual void display();
    void draw_border();
    void resize_window(int start_x, int end_x, int start_y, int end_y);
};