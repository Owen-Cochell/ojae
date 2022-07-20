#include <algorithm>

#include "TextRenderer.h"

TextRenderer::TextRenderer() {}

TextRenderer::TextRenderer(int screen_width, int screen_height) 
{
    available_fonts.push_back(16);

    font = 16;
    path = "assets/characters_font16.png";
    texture = TextureHandler::load_texture(path.c_str());
    cursor_pos = {0, 0};

    this->screen_width = screen_width;
    this->screen_height = screen_height;
}

TextRenderer::~TextRenderer() {}

void TextRenderer::add(std::string new_content)
{
    /*
    Adds a string to the contents 

    :PARAM new_content: Content to add
    */

    // If this content does not have a new line on the end, add a space 
    // character to it
    if(new_content.at(new_content.size() - 1) != '\n')
    {
        new_content += '\32';
    }

    contents.push_back(new_content);
}

void TextRenderer::add(std::string new_content, int amount)
{
    /*
    Adds a string to the contents n number of times

    :PARAM new_content: Content to add
    :PARAM amount: Number of times to add
    */

    for(int i = 0; i < amount; i++)
    {
        // If this content does not have a new line on the end, add a space 
        // character to it
        if(new_content.at(new_content.size() - 1) != '\n')
        {
            new_content += '\32';
        }

        contents.push_back(new_content);
    }
}

void TextRenderer::add_new_line(int amount)
{
    /*
    Adds n amount of new line characters to the contents

    :PARAM amount: Number of new lines to add
    */

    for(int i = 0; i < amount; i++)
    {
        contents.push_back("\n");
    }
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

    cursor_pos = {0, 0};

    for(std::string element : contents)
    {
        for(char c : element)
        {
            if(c == '\n')
            {
                cursor_pos.first = 0;
                cursor_pos.second += int(font * 1.5);
                continue;
            }

            else if(c == '\32')
            {
                cursor_pos.first += font; // Put an empty space between words
                continue;
            }

            // If the new character would exceed screen width dimensions, check if placing
            // a new character 1.5 font size down doesn't exceed screen height dimensions
            if(cursor_pos.first + font > screen_width
                && cursor_pos.second + int(font * 1.5) <= screen_height)
            {
                cursor_pos.first = 0;
                cursor_pos.second += int(font * 1.5);
            }

            // If the new character would exceed screen width and height dimensions
            // don't render it
            else if(cursor_pos.first + font > screen_width
                && cursor_pos.second + font > screen_height)
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
