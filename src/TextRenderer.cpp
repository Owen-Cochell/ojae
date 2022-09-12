#include <algorithm>
#include <SDL2/SDL.h>


#include "TextRenderer.h"

TextRenderer::TextRenderer() 
{
    font_width = 0;
    font_height = 0;
    texture_handler = nullptr;
    debugger = nullptr;
    texture = nullptr;
    start_x = 0;
    end_x = 0;
    start_y = 0;
    end_y = 0;
}

TextRenderer::TextRenderer(TextureHandler* _texture_handler, 
    Debugger* _debugger, int start_x, int end_x, int start_y, int end_y) 
{

    texture_handler = _texture_handler;
    debugger = _debugger;

    texture = nullptr;

    load_font("assets/ojae_font.json");

    this->start_x = start_x;
    this->end_x = end_x;
    this->start_y = start_y;
    this->end_y = end_y;
}

TextRenderer::~TextRenderer() {}

int TextRenderer::get_font_width() { return font_width; }

int TextRenderer::get_font_height() { return font_height; }

std::string TextRenderer::get_font_path() { return std::string(path); }

void TextRenderer::load_font(std::string json_path)
{
    debugger->log("[OUT] Loading font from path: ", true, false);
    debugger->log(json_path, false, true);

    if(!debugger->file_exists(json_path.c_str()))
    {
        debugger->log("[FAIL] TextRenderer.load_font -> Could not open file: ",
            true, false);
        debugger->log(json_path, false, true);
        exit(0);
    }

    file_stream.open(json_path, std::ios::in);

    if(file_stream.is_open())
    {
        file_stream >> j_loader;

        file_stream.close();
    }
    file_stream.clear();

    // Path to the png font file
    std::string targ_path = j_loader.at("path");

    if(!debugger->file_exists(targ_path.c_str()))
    {
        debugger->log("[FAIL] TextRenderer.load_font -> Could not open file: ",
            true, false);
        debugger->log(targ_path, false, true);
        exit(0);
    }

    path = targ_path;

    font_width = j_loader["width"];
    font_height = j_loader["height"];

    if(texture != nullptr) { SDL_DestroyTexture(texture); }
    texture = texture_handler->load_texture(path.c_str());
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

        src.x = (((c - 33) % 8) * font_width); // Character ascii value - 65 which would make '!' be 0
        src.y = (int((c - 33) / 8) * font_height); // Divide this by 8 so that if the ascii value exceeds 
            // a division of 8 it increments y by 1, to correspond with the png image.
        src.w = font_width;
        src.h = font_height;

        dest.x = x_pos;
        dest.y = y_pos;
        dest.w = font_width * 2;
        dest.h = font_height * 2;

        texture_handler->draw(texture, src, dest); // Draw the character
    }  
}

