#pragma once

#include <iostream>

#include "ECS.h"
#include "InputHandler.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"

struct InputComponent : public Component
{
    InputHandler* input_handler;

    InputComponent() {}

    InputComponent(InputHandler* _input_handler)
    {
        input_handler = _input_handler;
    }

    ~InputComponent() {}

    /**
     * @brief Modifies the Entity this Component is attatched to's position
     * based on the passed parameters
     * 
     * @param x_delta Change to the x value
     * @param y_delta Change to the y value
     */
    void modify_position(int x_delta, int y_delta)
    {
        // Assume that this entity has a transform component, as 
        // all entities should
        TransformComponent* t = 
            entity->getComponent<TransformComponent>();

        // Get the Component's current position
        int x_pos = t->x_pos;
        int y_pos = t->y_pos;

        // If the bound check for the entities at this position does not 
        // return true
        if(!bound_check(
            entity->entity_handler->get_entity_positions()
            [{x_pos + x_delta, y_pos + y_delta}]
        ))
        {
            return;
        }

        // Update the TransformComponent's Position
        t->y_pos = y_pos + y_delta;
        t->x_pos = x_pos + x_delta;
        
        // Update the Entity's EntityHandler's position of where 
        // the Entity this Component is attatched to lies
        entity->entity_handler->remove_entity(
            entity, x_pos, y_pos);
        entity->entity_handler->add_entity(
            entity, x_pos + x_delta, y_pos + y_delta);
    }

    /**
     * @brief Iterates through the keys in the input handler and performs logic
     * upon this Component's entity
     */
    void update() override 
    {

        for(Key* k : input_handler->get_active_keys())
        {

            switch(k->id)
            {
                // Up Arrow
                case SDLK_UP:

                    modify_position(0, -1);
                    input_handler->set_delay(k->id);
                    break;

                case SDLK_RIGHT:

                    modify_position(1, 0);
                    input_handler->set_delay(k->id);
                    break;

                case SDLK_DOWN:

                    modify_position(0, 1);
                    input_handler->set_delay(k->id);
                    break;

                case SDLK_LEFT:

                    modify_position(-1, 0);
                    input_handler->set_delay(k->id);
                    break;
            }
        }
    }
};
