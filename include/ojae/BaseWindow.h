#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <map>

#include "TextRenderer.h"
#include "TextureHandler.h"

/**
 * @brief Modular window for displaying text to the screen
 */
class BaseWindow
{

protected:

    SDL_Rect border_src; // Source Rect for all the border textures

    SDL_Rect top_border; // Destination Rect for the top border of the window
    SDL_Rect right_border;// Destination Rect for the right border of the window
    SDL_Rect bottom_border;// Destination Rect for the bottom border of the window
    SDL_Rect left_border;// Destination Rect for the left border of the window

    SDL_Texture* border; // Window Border Texture
    SDL_Texture* border_selected; // Selected Window Border Texture

    TextRenderer* text_renderer; // Instance of the TextRenderer
    SDL_Texture* font_texture; // Texture for the active font
    
    TextureHandler* texture_handler; // Instance of the TextureHandler

    const char* path; // Path to the font png

    int border_size; // Size of the border of the windows

    int start_x; // X Coordinate where the window begins
    int end_x; // X Coordinate where the window begins
    int start_y; // Y Coordinate where the window begins
    int end_y; // Y Coordinate where the window begins 

    bool taking_input; // Whether this info should handle keys from the input handler


public:

    BaseWindow();
    BaseWindow(TextureHandler* _texture_handler, int start_x, int end_x, 
        int start_y, int end_y, bool taking_input);
    ~BaseWindow();

    std::string get_font_path();

    /**
     * @brief Loads a new font into the TilemapWindow's TextRenderer
     * 
     * @param path Path to the new json font file
    */
    void load_font(const char* path);

    virtual void update();
    virtual void display();

    /**
     * @brief Draws the border around this Window
     */
    void draw_border();

    /**
     * @brief Resizes the window to new dimensinos
     * 
     * @param start_x Starting X positition
     * @param end_x Ending X position
     * @param start_y Starting Y position
     * @param end_y Engind Y Position
     */
    void resize_window(int start_x, int end_x, int start_y, int end_y);
};