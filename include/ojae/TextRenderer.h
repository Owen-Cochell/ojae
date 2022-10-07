#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <map>
#include <vector>
#include <string>

#include "TextureHandler.h"
#include "nlohmann/json.hpp"
#include "Character.h"

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

    std::string path; // Path to the font png

    int font_width; // Width in pixels of the current font
    int font_height; // Height in pixels of the current font

    std::vector<Character*> contents; // Contents to render each frame

    int start_x;
    int end_x;
    int start_y;
    int end_y;

public:

    TextRenderer();
    TextRenderer(TextureHandler* _texture_handler,
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
     * @param symbol Character to be rendered
     * @param x X Coordinate
     * @param y Y Coordinate
    */
    void add(char symbol, std::string color, int x, int y);

    /**
     * @brief Clears all content
     */
    void clear();

    /**
     * @brief Draws all content to the screen
     */
    void draw();
};