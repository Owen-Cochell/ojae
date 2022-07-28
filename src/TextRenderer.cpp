#include <algorithm>
#include <iostream>

#include "TextRenderer.h"
#include "Debug.h"

TextRenderer::TextRenderer() 
{
    font = 0;
    cursor_pos = {0, 0};
    start_x = 0;
    end_x = 0;
    start_y = 0;
    end_y = 0;
}

TextRenderer::TextRenderer(int start_x, int end_x, int start_y, int end_y) 
{
    available_fonts.push_back(16);

    font = 16;
    path = "assets/characters_font16.png";
    texture = TextureHandler::load_texture(path.c_str());
    cursor_pos = {0, 0};

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

void TextRenderer::add(std::string new_content)
{
    /*
    Adds a string to the contents at the character position of the passed 
    coordinates 

    :PARAM new_content: Content to add
    */

    for(char c : new_content)
    {
        if(c == '\n')
        {
            // Put the cursor on the next line
            set_cursor_pos(0, cursor_pos.second += 1);
            continue;
        }

        contents.push_back({c, std::pair<int,int>
        {
            start_x + (cursor_pos.first * font), 
            start_y + (cursor_pos.second * font * 1.5)
        }});

        // Increment the cursor's character position by 1
        cursor_pos.first++;
        

        // If the next character would print out of bounds
        if(start_x + (cursor_pos.first * font) > (end_x - font))
        {
            // Put the cursor on the next line
            set_cursor_pos(0, cursor_pos.second += 1);
        }
    }
}

void TextRenderer::add(char new_content)    
{
    if(new_content == '\n')
    {
        // Put the cursor on the next line
        set_cursor_pos(0, cursor_pos.second += 1);
        return;
    }

    contents.push_back({new_content, std::pair<int,int>
    {
        start_x + (cursor_pos.first * font), 
        start_y + (cursor_pos.second * font * 1.5)
    }});

    // Increment the cursor's character position by 1
    cursor_pos.first++;
    

    // If the next character would print out of bounds
    if(start_x + (cursor_pos.first * font) > (end_x - font))
    {
        // Put the cursor on the next line
        set_cursor_pos(0, cursor_pos.second += 1);
    }
}

void TextRenderer::clear()
{
    /*
    Clears the contents and resets the cursor position to the top left
    */

    contents.clear();
    set_cursor_pos(0, 0);
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

void TextRenderer::set_cursor_pos(int x, int y)
{
    /*
    Places the cursor in a new spot in the window if it is within bounds

    :PARAM x: X Coordinate
    :PARAM y: Y Coordinate 
    */
   
    if
    (
        x >= 0 &&
        x <= end_x - font && 
        y >= 0 &&
        y <= end_x - font
    )
    {
        cursor_pos.first = x;
        cursor_pos.second = y;
    }
}

void TextRenderer::draw_all()
{
    /*
    Loops through contents and displays the text to the screen
    */

    for(std::pair<char, std::pair<int, int>> element : contents)
    {

        char c = element.first;

        int x_pos = element.second.first;
        int y_pos = element.second.second;

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

