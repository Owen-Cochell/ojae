#pragma once

#include "../ECS.h"
#include "../InputHandler.h"
#include "../Components/TransformComponent.h"
#include "../CollisionHandler.h"
#include "../CommonDefs.h"

struct PlayerInput : public Script
{

    InputHandler* input_handler;

    PlayerInput(InputHandler* _input_handler)
    {
        name = "PlayerInput";
        input_handler = _input_handler;
    }

    Script* clone() override
    {
        return new PlayerInput(input_handler);
    }

    void start() override {}

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
            entity->get_component<TransformComponent>();

        // Get the Component's current position
        int x_pos = t->x_pos;
        int y_pos = t->y_pos;

        // If the traversable check for the entities at this position does not 
        // return true
        if(!CollisionHandler::is_traversable(entity, x_pos + x_delta, 
            y_pos + y_delta))
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

    void set_position(int x, int y)
    {
        TransformComponent* c =
            entity->get_component<TransformComponent>();
        modify_position(-(c->x_pos - x), -(c->y_pos - y));
    }

    /**
     * @brief Iterates through the keys in the input handler and performs logic
     * upon this Component's entity
     */
    void update() override 
    {

        Uint64 init;
        int modify_time;
        int handler_time;
        

        for(Key* k : input_handler->get_active_keys())
        {

            switch(k->id)
            {
                // Up Arrow
                case SDLK_UP:

                    init = SDL_GetTicks64();
                    modify_position(0, -1);
                    init = SDL_GetTicks64();
                    input_handler->set_delay(k->id);
                    handler_time = SDL_GetTicks64() - init;
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

                case 't':

                    set_position(1, 1);
                    input_handler->set_delay(k->id);
                    break;
            }
        }
    }

};
