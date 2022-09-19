#pragma once

#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#include "Tile.h"
#include "Debugger.h"

class EntityManager;

/**
 * @brief A Tile with extended logic for moving and interacting.
 */
class Entity: public Tile
{

protected:

    EntityManager* entity_manager; // Instance of the EntityManager

public:


    Entity();

    Entity(std::string name, std::string color, char character, int priority);

    ~Entity() override;

    virtual void update();  // Method called upon each frame refresh
    // virtual void start();  // Method called when entity is added
    // virtual void stop();  // Method called when entity is removed

    void set_entity_manager(EntityManager* _entity_manager);

};

struct entity_greater_priority
{
    inline bool operator()(Entity* a, Entity* b)
    {
        return a->get_priority() > b->get_priority();
    }
};

class EntityManager
{

private:

    Debugger* debugger; // Instance of the Debugger

    /**
     * @brief Map of coordinate positions to a vector of entities
     */
    std::map<std::pair<int,int>, std::vector<Entity*>> entities;

    int width; // Width in tiles limit for entity movement
    int height; // Height in tiles limit for entity movement

public:

    EntityManager();
    EntityManager(Debugger* _debugger, int _width, int _height);
    ~EntityManager();

    std::map<std::pair<int,int>, std::vector<Entity*>> get_entities();

    /**
     * @brief Checks if a coordinate point in the map is within the 
     * constrictions
     * 
     * @param x X Position
     * @param y Y Position
     * @return True if the spot is available to move to
     */
    bool bound_check(int x, int y);

    /**
     * @brief Adds an entity to the map of entities at a given position
     * 
     * @param e Entity to add
     */
    void add_entity(Entity* e, int x, int y);

    /**
     * @brief Removes an entity from the map of entities. Uses the entity's 
     * current position to target which position to remove it from
     * 
     * @param e Entity to remove
     * @param deconstruct Remove the Entity from heap memory
     */
    void remove_entity(Entity* e, bool deconstruct = false);

    /**
     * @brief Moves an entity to a new position in the map
     * 
     * @param e Entity to move
     * @param x X Position
     * @param y Y Position
     */
    void move_entity(Entity* e, int x, int y);

};


// Owen

// class InputEntity: public Entity
// {
//     /*
//     InputEntity - An entity that takes input from somewhere.

//     This entity usually takes input from the InputHandler,
//     and is usually the thing that is controlled by the player.

//     We offer easy to use methods for adding callbacks to the input handler.
//     */

//     public:

//         InputEntity() 
//         {
//             character = ' ';
//             x_pos = 0;
//             y_pos = 0;
//             priority = 0;
//             traversable = true;
//         }

//         InputEntity(std::string name, char character, int priority)
//         {
//             this->name = name;
//             this->character = character;
//             x_pos = 0;
//             y_pos = 0;
//             this->priority = priority;
//             traversable = false;
//         }

//         ~InputEntity() 
//         {

//         }

//         void want_key(int key);  // method used to register keys to this entity

//         virtual void on_input();  // Method called when valid input for this class is encountered

// };

// class MovementEntity: public Entity
// {
//     /*
//     MovementEntity - Entity that moves over time.

//     This entity makes the process of moving very easy and configurable.
//     We keep track of the position of this entity, as always,
//     along with the X and Y velocity/acceleration.

//     The acceleration/velocity is determined in pixels per second.
//     These work as you would expect, a velocity of 10px/s
//     would change the position 10 pixels each second,
//     and an acceleration of 10px/s would add 10 pixels to the velocity each second.

//     The method used to calculate these values is calc_move(),
//     which will change the position of this object each frame in relation
//     to the velocity and acceleration values.
//     */

//     private:

//         int x_vel;  // X Velocity
//         int y_vel;  // Y Velocity

//         int x_acc;  // X Acceleration
//         int y_acc;  // Y Acceleration

//         uint64_t last = 0;  // Last tick value we received
//         uint64_t freq = SDL_GetPerformanceFrequency();  // Number of ticks per second

//     public:

//         MovementEntity() 
//         {
//             character = ' ';
//             x_pos = 0;
//             y_pos = 0;
//             priority = 0;
//             traversable = true;
//         }

//         MovementEntity(std::string name, char character, int priority)
//         {
//             this->name = name;
//             this->character = character;
//             x_pos = 0;
//             y_pos = 0;
//             this->priority = priority;
//             traversable = false;
//         }

//         ~MovementEntity() 
//         {

//         }

//         void calc_move();  // Calculates the current value based on time
// };
