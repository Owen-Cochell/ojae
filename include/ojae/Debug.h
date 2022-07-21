#pragma once 

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

static void display_rect(SDL_Rect rect)
{
    std::cout << "x: " << rect.x << "\n";
    std::cout << "y: " << rect.y << "\n";
    std::cout << "w: " << rect.w << "\n";
    std::cout << "h: " << rect.h << "\n\n";
}