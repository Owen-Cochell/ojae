#pragma once

#include "../ECS.h"
#include "../Random.h"
#include "../Components/TransformComponent.h"
#include "../CollisionHandler.h"

struct RandomMovement : public Script
{

    int frame_delay = 0; // Number of frames between each move call

    /**
     * @brief Current number of frames this entity is waiting until its next 
     * move call
     */
    int current_frame_delay = 0;

    /**
     * @brief (n / 10) Chance that this entity will move on its move call
     */
    int move_chance = 0;

    RandomMovement(int _frame_delay, int _move_chance) 
    {
        frame_delay = _frame_delay;
        current_frame_delay = _frame_delay;

        if(_move_chance > 10) _move_chance = 10;

        move_chance = _move_chance;

        name = "RandomMoveComponent";
    }

    RandomMovement(const RandomMovement& s) : Script(s)
    {
        frame_delay = s.frame_delay;
        current_frame_delay = s.current_frame_delay;
        move_chance = s.move_chance;
    }

    Script* clone() override
    {
        RandomMovement* new_s = new RandomMovement(frame_delay, move_chance);
        new_s->current_frame_delay = current_frame_delay;
        return new_s;
    }

    void update() override
    {

        // If this entity is still waiting to move
        if(current_frame_delay > 0)
        {       
            current_frame_delay--;
            return;
        }

        // Check if this entity is randomly moving this turn
        int ran_num = Random::get_random_num(1, 10);

        // The enemy was not selected to move this turn. It will try again on 
        // its next move call
        if(ran_num > move_chance)
        {
            current_frame_delay = frame_delay;
            return;
        }

        TransformComponent* c = entity->get_component<TransformComponent>();

        std::vector<std::pair<int,int>> available_moves;

        for(int y = c->y_pos - 1; y <= c->y_pos + 1; y++)
        {
            for(int x = c->x_pos - 1; x <= c->x_pos + 1; x++)
            {
                // If we aren't looking at the tile that is this entity's
                // current position, and the tile we are looking at is 
                // traversable
                if((y != 0 || x != 0) &&
                    CollisionHandler::is_traversable(entity, x, y))
                {
                    available_moves.push_back({x, y});
                }
            }
        }

        if(available_moves.size() == 0)
        {
            return;
        }

        // Get a random pair from our available moves
        std::pair<int, int> targ = 
            Random::get_random_vector_element(available_moves);

        entity->entity_handler->remove_entity(entity, c->x_pos, c->y_pos);
        entity->entity_handler->add_entity(entity, targ.first, targ.second);

        c->set_position(targ.first, targ.second);
        
        current_frame_delay = frame_delay;
    }

};