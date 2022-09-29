#pragma once

#include "ECS.h"
#include "Components/ColliderComponent.h"

struct CollisionHandler
{

static bool is_traversable(Entity* e, int x, int y)
{
    // Entities at the position the passed entity is attempting to move to
    std::vector<Entity*> entities = 
        e->entity_handler->get_entity_positions()[{x, y}];

    // Iterate through the entities at the target position
    for(Entity* e : entities)
    {
        // If the Entity has a collider component
        if(e->has_component<ColliderComponent>())
        {
            // If the entity collides with the component, and is blocked
            if(!e->get_component<ColliderComponent>()->collide(e))
            {
                return false;
            }
        }
    }

    return true;
}

};
