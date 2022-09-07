#pragma once 

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

static void display_rect(SDL_Rect rect, const char* name)
{
    std::cout << name << ":\n";
    std::cout << "x: " << rect.x << "\n";
    std::cout << "y: " << rect.y << "\n";
    std::cout << "w: " << rect.w << "\n";
    std::cout << "h: " << rect.h << "\n\n";
}

static void display_int_pair(std::pair<int,int> element, const char* name)
{
    std::cout << name << ":\n";
    std::cout << "First: " << element.first << "\n";
    std::cout << "Second: " << element.second << "\n\n";
}