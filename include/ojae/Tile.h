#pragma once

#include <string>

/**
 * @brief Basic character that can be added to a tilemap. Offers little 
 * functionality */
class Tile
{

    /*
    A 'Tile' is a texture on the screen.
    */

protected:

    std::string name; // Name of the tile

    char character; // Visual character that is rendered

    int x_pos; // X Coordinate
    int y_pos; // Y Coordinate
    int priority; // Rendering priority of the Tile

    bool traversable; // If this tile is traversable by things that can move
    bool interactable; // If this tile is able to be interacted with

public:

    Tile()
    {   
        character = ' ';
        x_pos = 0;
        y_pos = 0;
        priority = 0;
        traversable = true;
        interactable = false;
    }

    Tile(std::string _name, char _character, 
        bool _traversable, int _priority)
    {
        this->name = _name;
        this->character = _character;
        x_pos = 0;
        y_pos = 0;
        priority = _priority;
        traversable = _traversable;
        interactable = false;
    }

    virtual ~Tile() {}

    std::string get_name() { return name; }

    char get_character() { return character; }

    int get_x() { return x_pos; }

    int get_y() { return y_pos; }

    int get_priority() { return priority; }

    bool is_traversable() { return traversable; }

    bool is_interactable() { return interactable; }

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
    
    /**
     * @brief Called whenever an entity attempts to move/interact with this 
     * tile */
    virtual void interact() {}
};
