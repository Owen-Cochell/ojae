#pragma once

#include <string>

class Entity
{

private:

    std::string name; // Name of the entity

    char character; // Visual character that is rendered
    
    int x_pos; // X Coordinate
    int y_pos; // Y Coordinate
    int priority; // Rendering priority of the Tile

    bool traversable; // If this entity is traversable by things that can move

public:

    Entity() 
    {
        character = ' ';
        x_pos = 0;
        y_pos = 0;
        priority = 0;
        traversable = true;
    }

    Entity(std::string name, char character, int priority)
    {
        this->name = name;
        this->character = character;
        x_pos = 0;
        y_pos = 0;
        this->priority = priority;
        traversable = false;
    }

    ~Entity() 
    {

    }

    std::string get_name() { return name; }

    char get_character() { return character; }

    int get_x() { return x_pos; }
    
    int get_y() { return y_pos; }

    int get_priority() { return priority; }

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
