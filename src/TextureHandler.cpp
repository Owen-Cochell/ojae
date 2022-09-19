#include <iostream>
#include <fstream>

#include "TextureHandler.h"
#include "Demo.h"

// Constructors/Deconstructors

TextureHandler::TextureHandler()
{
    renderer = nullptr;
}

TextureHandler::TextureHandler(SDL_Renderer* _renderer, 
    Debugger* _debugger)
{
    renderer = _renderer;
    debugger = _debugger;
}

TextureHandler::~TextureHandler() {}

// Public Functions

SDL_Texture* TextureHandler::load_texture(const char* path)
{

    try
    {
        if(!debugger->file_exists(path))
        {
            throw path;
        }
    }

    catch(const char* path)
    {
        debugger->log("[FAIL] TextureHandler.load_texture -> Could not open"
            " file: ", true, false);
        debugger->log(path, false, false);

        exit(0);
    }

    debugger->log("[OUT] Creating texture from path: ", true, false);
    debugger->log(path, false);

    SDL_Surface* temp_surface = IMG_Load(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp_surface);

    SDL_FreeSurface(temp_surface);

    return texture;
}

void TextureHandler::add_color(Color* color)
{
    colors.emplace(color->get_name(), color);
}

std::map<std::string, Color*> TextureHandler::get_colors(){ return colors; }

void TextureHandler::draw(SDL_Texture* texture, SDL_Rect& src, SDL_Rect& dest,
    std::string color)
{

    // If an empty string was not passed
    if(color.size() != 0)
    {

        // If the color doesn't exist in the registered colors map
        if(colors.count(color) == 0)
        {
            debugger->log("[FAIL] TextureHandler.draw() -> Color not "
                "registered: ", true, false);
            debugger->log(color, false, true);
            debugger->log("[OUT] Exiting...");
            exit(0);
        }

        Color* targ_color = colors[color];

        SDL_SetTextureColorMod(texture, targ_color->get_r(), 
            targ_color->get_g(),targ_color->get_b());
    }

    SDL_RenderCopy(renderer, texture, &src, &dest);
}