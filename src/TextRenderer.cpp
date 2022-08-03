#include <algorithm>
#include <SDL2/SDL.h>

#include "TextRenderer.h"
#include "Debug.h"

TextRenderer::TextRenderer() 
{
    font = 0;
    start_x = 0;
    end_x = 0;
    start_y = 0;
    end_y = 0;
}

TextRenderer::TextRenderer(int start_x, int end_x, int start_y, int end_y,
    int time_limit) 
{
    available_fonts.push_back(16);

    font = 16;
    path = "assets/characters_font16.png";
    texture = TextureHandler::load_texture(path.c_str());

    this->start_x = start_x;
    this->end_x = end_x;
    this->start_y = start_y;
    this->end_y = end_y;
}

TextRenderer::~TextRenderer() {}

int TextRenderer::get_font() { return font; }

bool TextRenderer::check_font(int font_size)
{
    /*
    Checks if a given font is available to use

    :PARAM font_size: Font to check
    */

    return std::find(available_fonts.begin(), available_fonts.end(),
        font_size) != available_fonts.end();
}

void TextRenderer::add(char new_content, int x, int y)    
{
    /*
    Adds a character to the text renderer at the specified coordinates

    :PARAM new_content: Character to add
    :PARAM x: X Coordinate
    :PARAM y: Y Coordinate
    */

    contents.push_back({{x,y}, new_content});
}

void TextRenderer::clear()
{
    /*
    Clears the contents
    */

    contents.clear();
}

void TextRenderer::set_font(int new_font)
{
    /*
    Sets the font to the new font if it is supported 

    :PARAM new_font: New font to be set
    */

    if(check_font(new_font))
    {
        font = new_font;
        path = "assets/characters_font" + std::to_string(font) + ".png";
        SDL_DestroyTexture(texture);
        texture = TextureHandler::load_texture(path.c_str());
    }
}

void TextRenderer::draw()
{
    /*
    Loops through contents and displays the text to the screen
    */

    for(std::pair<std::pair<int,int>, char> element : contents)
    {
        //display_int_pair(element.first, &element.second);

        char c = element.second;

        int x_pos = element.first.first;
        int y_pos = element.first.second;

        src.x = (((c - 33) % 8) * font) - 1; // Character ascii value - 65 which would make '!' be 0
        src.y = (((c - 33) / 8) * font) - 1; // Divide this by 8 so that if the ascii value exceeds 
            // a division of 8 it increments y by 1, to correspond with the png image.
        src.w = font;
        src.h = font;

        dest.x = x_pos;
        dest.y = y_pos;
        dest.w = font;
        dest.h = font;

        TextureHandler::draw(texture, src, dest); // Draw the character
    }  
}

