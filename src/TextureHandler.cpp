#include <iostream>

#include "TextureHandler.h"
#include "FileHandler.h"
#include "Demo.h"

SDL_Texture* TextureHandler::load_texture(const char* path)
{

    try
    {
        if(!file_exists(path))
        {
            throw path;
        }
    }

    catch(const char* path)
    {
        std::cout << "TextureHandler.load_texture -> Could not open file: " << path;
        exit(0);
    }

    SDL_Surface* temp_surface = IMG_Load(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Demo::renderer, temp_surface);

    SDL_FreeSurface(temp_surface);

    return texture;
}

void TextureHandler::draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Demo::renderer, texture, &src, &dest, 0, 0, flip);
}