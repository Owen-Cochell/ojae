#pragma once

#include <string>
#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#include "Tile.h"

class Entity: public Tile
{

    /*
    An 'Entity' is a texture that is given the ability 
    to run arbitrary code on each frame refresh.
    */

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

    virtual void update() {};  // Method called upon each frame refresh
    virtual void start() {};  // Method called when entity is added
    virtual void stop() {};  // Method called when entity is removed

};

class InputEntity: public Entity
{
    /*
    InputEntity - An entity that takes input from somewhere.

    This entity usually takes input from the InputHandler,
    and is usually the thing that is controlled by the player.

    We offer easy to use methods for adding callbacks to the input handler.
    */

    public:

        InputEntity() 
        {
            character = ' ';
            x_pos = 0;
            y_pos = 0;
            priority = 0;
            traversable = true;
        }

        InputEntity(std::string name, char character, int priority)
        {
            this->name = name;
            this->character = character;
            x_pos = 0;
            y_pos = 0;
            this->priority = priority;
            traversable = false;
        }

        ~InputEntity() 
        {

        }

        void want_key(int key);  // method used to register keys to this entity

        virtual void on_input();  // Method called when valid input for this class is encountered

};

class MovementEntity: public Entity
{
    /*
    MovementEntity - Entity that moves over time.

    This entity makes the process of moving very easy and configurable.
    We keep track of the position of this entity, as always,
    along with the X and Y velocity/acceleration.

    The acceleration/velocity is determined in pixels per second.
    These work as you would expect, a velocity of 10px/s
    would change the position 10 pixels each second,
    and an acceleration of 10px/s would add 10 pixels to the velocity each second.

    The method used to calculate these values is calc_move(),
    which will change the position of this object each frame in relation
    to the velocity and acceleration values.
    */

    private:

        int x_vel;  // X Velocity
        int y_vel;  // Y Velocity

        int x_acc;  // X Acceleration
        int y_acc;  // Y Acceleration

        uint64_t last = 0;  // Last tick value we received
        uint64_t freq = SDL_GetPerformanceFrequency();  // Number of ticks per second

    public:

        MovementEntity() 
        {
            character = ' ';
            x_pos = 0;
            y_pos = 0;
            priority = 0;
            traversable = true;
        }

        MovementEntity(std::string name, char character, int priority)
        {
            this->name = name;
            this->character = character;
            x_pos = 0;
            y_pos = 0;
            this->priority = priority;
            traversable = false;
        }

        ~MovementEntity() 
        {

        }

        void calc_move();  // Calculates the current value based on time
};
