#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <vector>
#include <string>

#include "TextureHandler.h"

class TextRenderer
{
    /*
    Handles the drawing of text to the SDL Window
    */

private:

    SDL_Rect src, dest;
    SDL_Texture* texture;

    std::string path; // Path to the current character png

    int font; // Font size of the text being displayed

    std::vector<int> available_fonts; // List of available fonts 
    std::vector<std::pair<std::pair<int, int>, char>> contents; // List of content
        // to render each frame

    int start_x;
    int end_x;
    int start_y;
    int end_y;

public:

    TextRenderer();
    TextRenderer(int start_x, int end_x, int start_y, int end_y);
    ~TextRenderer();

    int get_font();

    bool check_font(int font_size);

    void add(char new_content, int x, int y);
    void clear();
    void set_font(int font_size);
    void draw();
};