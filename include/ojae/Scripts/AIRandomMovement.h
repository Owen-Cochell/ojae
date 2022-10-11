#pragma once

#include "../ECS.h"
#include "../Random.h"
#include "../Components/TransformComponent.h"
#include "../Components/AIMovementComponent.h"
#include "../CollisionHandler.h"

struct AIRandomMovement : public Script
{
    /**
     * @brief (n / 10) Chance that this entity will move on its move call
     */
    int move_chance = 0;


    AIRandomMovement(int _move_chance) 
    {
        move_chance = _move_chance;
        name = "AIRandomMove";
    }

    Script* clone() override
    {
        return new AIRandomMovement(move_chance);
    }

    void update() override
    {
        AIMovementComponent* move_c = 
            entity->get_component<AIMovementComponent>();

        if(!move_c->can_move()) return;

        // Check if this entity is randomly moving this turn
        int ran_num = Random::get_random_num(1, 10);

        // The enemy was not selected to move this turn. It will try again on 
        // its next move call
        if(ran_num > move_chance)
        {
            move_c->current_frame_delay = move_c->frame_delay;
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
        int index = Random::get_random_num(0, available_moves.size() - 1);
        std::pair<int, int> targ = available_moves.at(index);

        entity->get_component<AIMovementComponent>()->move(targ.first, targ.second);
        

        move_c->reset_frames();
    }

};