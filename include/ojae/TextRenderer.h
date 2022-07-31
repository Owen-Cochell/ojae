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
    std::vector<std::pair<char, std::pair<int, int>>> contents; // List of the content to render

    std::pair<int, int> cursor_pos;

    int start_x;
    int end_x;
    int start_y;
    int end_y;

    int largest_y; // Largest y coordinate in our contents

public:

    int display_start; // Starting index of where our y is rendering

    TextRenderer();
    TextRenderer(int start_x, int end_x, int start_y, int end_y);
    ~TextRenderer();

    int get_font();
    int get_largest_y();

    bool check_font(int font_size);

    void add(std::string new_content);
    void add(char new_content);
    void clear();
    void set_font(int font_size);
    void set_cursor_pos(int x, int y);
    void draw_all();
};