#pragma once 

#include <string>

/**
 * @brief Contains data for printing chars to the screen. 
 */
struct Character
{
    std::string color; // Color of the

    char symbol; // Symbol representing the character

    int x_pos; // X Position
    int y_pos; // Y Position

    Character()
    {
        symbol = ' ';
        x_pos = 0;
        y_pos = 0;
    }

    Character(char _symbol, std::string _color, int x, int y)
    {
        symbol = _symbol;
        color = _color;
        x_pos = x;
        y_pos = y;
    }
};
