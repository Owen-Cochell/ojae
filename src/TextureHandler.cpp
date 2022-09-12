
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

void TextureHandler::draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(renderer, texture, &src, &dest, 0, 0, flip);
}