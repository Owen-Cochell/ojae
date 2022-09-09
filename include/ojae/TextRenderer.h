#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <map>
#include <vector>
#include <string>

#include "TextureHandler.h"
#include "nlohmann/json.hpp"

class TextRenderer
{
    /*
    Handles the drawing of text to the SDL Window
    */

private:

    SDL_Rect src, dest;
    SDL_Texture* texture;

    nlohmann::json j_loader; // Instance of the Json Object
    std::fstream file_stream; // Instance of the fstream

    TextureHandler* texture_handler; // Instance of the TextureHandler
    Debugger* debugger; // Instance of the Debugger

    std::string path; // Path to the font png

    int font_width; // Width in pixels of the current font
    int font_height; // Height in pixels of the current font

    // std::vector<int> available_fonts; // List of available fonts 
    std::vector<std::pair<std::pair<int, int>, char>> contents; // List of content
        // to render each frame

    int start_x;
    int end_x;
    int start_y;
    int end_y;

public:

    TextRenderer();
    TextRenderer(TextureHandler* _texture_handler, Debugger* _debugger,
        int start_x, int end_x, int start_y, int end_y);
    ~TextRenderer();

    int get_font_width();
    int get_font_height();

    std::string get_font_path();

    /**
     * @brief Loads a font into the TextRenderer from a json file containing
     * the relevent data for the font png being loaded
     * 
     * @param json_path Path to the json font file 
     * */
    void load_font(std::string json_path);

    /**
     * @brief Adds a character to a specific coordinate on the screen
     * 
     * @param new_content Character to be rendered
     * @param x X Coordinate
     * @param y Y Coordinate
    */
    void add(char new_content, int x, int y);

    /**
     * @brief Clears all content
     */
    void clear();

    /**
     * @brief Draws all content to the screen
     */
    void draw();
};