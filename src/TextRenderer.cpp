#include <algorithm>

#include "TextRenderer.h"

TextRenderer::TextRenderer() {}

TextRenderer::TextRenderer(int start_x, int end_x, int start_y, int end_y) 
{
    available_fonts.push_back(16);

    font = 16;
    path = "assets/characters_font16.png";
    texture = TextureHandler::load_texture(path.c_str());
    cursor_pos = {start_x, start_y};

    this->start_x = start_x;
    this->end_x = end_x;
    this->start_y = start_y;
    this->end_y = end_y;
}

TextRenderer::~TextRenderer() {}

void TextRenderer::add(std::string new_content, int x, int y)
{
    /*
    Adds a string to the contents with a specified coordinate 

    :PARAM new_content: Content to add
    :PARAM x: X coordinate to draw the text
    :PARAM y: Y coordinate to draw the text
    */

    contents.emplace(new_content, std::pair<int, int> {x, y});
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


    // If this int is in the list of supported fonts
    if(std::find(available_fonts.begin(), available_fonts.end(), new_font)
        != available_fonts.end())
    {
        font = new_font;
        path = "assets/characters_font" + std::to_string(font) + ".png";
        SDL_DestroyTexture(texture);
        texture = TextureHandler::load_texture(path.c_str());
    }
}

void TextRenderer::draw_all()
{
    /*
    Loops through contents and displays the text to the screen
    */

    for(std::pair<std::string, std::pair<int, int>> element : contents)
    {
        cursor_pos = element.second;

        for(char c : element.first)
        {

            if(c == '\32')
            {
                cursor_pos.first += font; // Put an empty space between words
                continue;
            }

            // If the new character would exceed screen width dimensions, check if placing

            // If the new character would exceed screen width or height dimensions
            // don't render it
            else if(cursor_pos.first + font > end_x
                || cursor_pos.second + font > end_y)
            {
                return;
            }

            src.x = ((c - 33) % 8) * font; // Character ascii value - 65 which would make '!' be 0
            src.y = ((c - 33) / 8) * font; // Divide this by 8 so that if the ascii value exceeds 
                // a division of 8 it increments y by 1, to correspond with the png image.
            src.w = font;
            src.h = font;

            dest.x = cursor_pos.first;
            dest.y = cursor_pos.second;
            dest.w = font;
            dest.h = font;

            TextureHandler::draw(texture, src, dest); // Draw the character

            cursor_pos.first += font; // Increment the cursor so that the next
                // letter does not overlap this one
        }
    }  
}
