#pragma once

#include <SDL.h>
#include <SDL_Image.h>

class TextureHandler
{

public:

    static SDL_Texture* load_texture(const char* path);
    static void draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:

};