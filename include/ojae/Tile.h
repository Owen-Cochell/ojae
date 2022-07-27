#pragma once

#include <string>

class Tile
{

private:

    std::string name; // Name of the tile

    char character; // Visual character that is rendered
    
    int x_pos; // X Coordinate
    int y_pos; // Y Coordinate
    int priority; // Rendering priority of the Tile

    bool traversable; // If this tile is traversable by things that can move

public:

    Tile()
    {   
        character = ' ';
        x_pos = 0;
        y_pos = 0;
        priority = 0;
        traversable = true;
    }

    Tile(std::string name, char character, bool traversable, int priority)
    {
        this->name = name;
        this->character = character;
        x_pos = 0;
        y_pos = 0;
        this->priority = priority;
        this->traversable = traversable;
    }

    ~Tile() {}

    std::string get_name() { return name; }

    char get_character() { return character; }

    int get_x() { return x_pos; }

    int get_y() { return y_pos; }

    int get_priority() { return priority; }

    bool is_traversable() { return traversable; }

    void set_position(int x, int y)
    {
        /*
        Sets new x and y coordinates for the tile

        :PARAM x: X Coordinate
        :PARAM y: Y Coordinate
        */

        x_pos = x;
        y_pos = y;
    }

};
