#pragma once

#include <string>

class Entity
{

private:

    std::string name; // Name of the entity

    char character; // Visual character that is rendered
    
    int x_pos; // X Coordinate
    int y_pos; // Y Coordinate

    bool traversable; // If this entity is traversable by things that can move


public:

    Entity() {}
    ~Entity() {}

    std::string get_name() { return name; }

    char get_character() { return character; }

    int get_x() { return x_pos; }
    int get_y() { return y_pos; }

    bool is_traversable() { return traversable; }

    void set_position(int x, int y)
    {
        /*
        Sets new x and y coordinates for the entity

        :PARAM x: X Coordinate
        :PARAM y: Y Coordinate
        */

        x_pos = x;
        y_pos = y;
    }


};
