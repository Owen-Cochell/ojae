#pragma once

#include <string>

class Item
{

private:

    std::string name; // Name of the item

    char character; // Visual character that is rendered
    
    int x_pos; // X Coordinate
    int y_pos; // Y Coordinate

    bool traversable; // If this item is traversable by things that can move
    bool held; // If this item is held by an entity

public:

    Item()
    {
        character = ' ';
        x_pos = 0;
        y_pos = 0;
        traversable = true;
        held = false;
    }

    Item(std::string name, char character, bool traversable)
    {
        this->name = name;
        this->character = character;
        x_pos = 0;
        y_pos = 0;
        this->traversable = traversable;
        held = false;
    }

    ~Item() {}

    std::string get_name() { return name; }

    char get_character() { return character; }

    int get_x() { return x_pos; }
    int get_y() { return y_pos; }

    bool is_traversable() { return traversable; }

    void set_position(int x, int y)
    {
        /*
        Sets new x and y coordinates for the item 

        :PARAM x: X Coordinate
        :PARAM y: Y Coordinate
        */

        x_pos = x;
        y_pos = y;
    }
};

