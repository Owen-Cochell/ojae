#pragma once 

#include "../ECS.h"
#include "../Components/DialogueComponent.h"
#include "../Components/TransformComponent.h"

struct DeclareMove : public Script
{
    std::pair<int, int> last_pos {0, 0}; 

    Script* clone() override 
    {
        return new DeclareMove();
    }

    void start() override
    {
        if(entity->has_component<TransformComponent>())
        {
            TransformComponent* t = 
                entity->get_component<TransformComponent>();

            last_pos = std::pair<int,int>{t->x_pos, t->y_pos};

        }
    }

    void update() override
    {

        if(entity->has_component<DialogueComponent>())
        {   
            TransformComponent* t  = 
                entity->get_component<TransformComponent>();

            // If the entity's position is different than the last frame,
            // meaning it moved
            if(t->x_pos != last_pos.first || t->y_pos != last_pos.second)
            {
                DialogueComponent* d = 
                entity->get_component<DialogueComponent>();

                std::string speech = entity->name + ": I moved";

                d->text_funnel->add(speech, "Blue");

                last_pos = std::pair<int,int>{t->x_pos, t->y_pos};
            }
        }
    }
};
