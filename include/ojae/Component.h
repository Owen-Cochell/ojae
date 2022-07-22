#pragma once

#include <string>

#include "Sprite.h"

class Component
{

private:

    Sprite* sprite; // Instance of the sprite connected to this object

    std::string name; // Name of the object 
    int x_pos = 0; // X position of the object
    int y_pos = 0; // Y position of object 


public:

    Component()
    {
        sprite = new Sprite();
    }

    Component(std::string name, const char* texture_path, int src_x, int src_y, int src_w, int src_h, int dest_x, int dest_y,
        int dest_w, int dest_h)
    {
        this->name = name;
        sprite = new Sprite(texture_path, src_x, src_y, src_w, src_h, dest_x,
            dest_y, dest_w, dest_h);
        x_pos = dest_x;
        y_pos = dest_y;
    }
    
    ~Component()
    {
        sprite->~Sprite();
    }

    void draw()
    {
        sprite->draw();
    }

    void update()
    {
        /*
        Called once per frame. Updates the sprite's position to reflect 
        the object's position
        */
        

        sprite->set_position(x_pos, y_pos);
    }

    void increment_x(int amount)
    {
        /*
        Increments the X position by n amount

        :PARAM amount: Amount to increment by
        */

        x_pos += amount;
    }

    void increment_y(int amount)
    {
        /*
        Increments the Y position by n amount

        :PARAM amount: Amount to increment by
        */

        y_pos += amount;
    }

};