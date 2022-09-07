#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Debugger.h"

class TextureHandler
{

private:

    SDL_Renderer* renderer; // Instance of the renderer

    Debugger* debugger; // Instance of the Debugger

public:

    TextureHandler();
    TextureHandler(SDL_Renderer* renderer, Debugger* _debugger);
    ~TextureHandler();

    /**
     * @brief Loads a png image from a directory and converts it into an SDL
     * Texture
     * @param path Directory of the png image
     * @return SDL_Texture* */
    SDL_Texture* load_texture(const char* path);

    /**
     * @brief Loads a texture into the renderer to be drawn.
     * @param texture Texture to be drawn
     * @param src Source Rect for rendering
     * @param dest Destination Rect for rendering
     * @param flip If the sprite should be flipped horizontally */
    void draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip = SDL_FLIP_NONE);

};