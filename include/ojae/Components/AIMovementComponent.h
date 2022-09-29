#pragma once

#include "../ECS.h"
#include "../Random.h"

struct AIMovementComponent : public Component
{

    int frame_delay = 0; // Number of frames between each move call
    
    /**
     * @brief Current number of frames this entity is waiting until its next 
     * move call
     */
    int current_frame_delay = 0;
    
    AIMovementComponent(int _frame_delay)
    {
        name = "AIMovement";

        frame_delay = _frame_delay;
        current_frame_delay = _frame_delay;
    }

    Component* clone() override
    {
        return new AIMovementComponent(frame_delay);
    }

    bool can_move()
    {
        // If this entity is still waiting to move
        if(current_frame_delay > 0)
        {       
            current_frame_delay--;
            return false;
        }

        return true;
    }

    void reset_frames() { current_frame_delay = frame_delay; }

    void move(int x, int y)
    {
        TransformComponent* this_t = 
            entity->get_component<TransformComponent>();

        entity->entity_handler->remove_entity(entity, this_t->x_pos, this_t->y_pos);
        entity->entity_handler->add_entity(entity, x, y);

        this_t->set_position(x, y);
    }
};
