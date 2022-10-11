#pragma once

#include "ECS.h"
#include "Components/ColliderComponent.h"
#include "Debug.h"
#include "CommonDefs.h"

struct CollisionHandler
{

    static bool is_traversable(Entity* e, int x, int y)
    {
        // Entities at the position the passed entity is attempting to move to
        std::vector<Entity*> entities = 
            e->entity_handler->get_entities_at_position(x, y);

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

    static std::vector<std::pair<int, int>> 
        get_available_surrounding_positions(Entity* e , int _x, int _y)
        {
            std::vector<std::pair<int, int>> available_positions;

            for(int y = _y - 1; y <= _y + 1; y++)
            {
                for(int x = _x - 1; x <= _x + 1; x++)
                {
                    // If we aren't looking at the tile that is this entity's
                    // current position, and the tile we are looking at is 
                    // traversable
                    if((y != 0 || x != 0) &&
                        is_traversable(e, x, y))
                    {
                        available_positions.push_back({x, y});
                    }
                }
            }

            return available_positions;
        }

};
