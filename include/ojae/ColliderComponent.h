#pragma once 

#include "ECS.h"

static bool bound_check(std::vector<Entity*> entities)
{
    // Iterate through the entities 
    for(Entity* targ_e : entities)
    {
        // Iterate through the tags of each entity
        for(std::string t : targ_e->get_tags())
        {
            // If this entity contains the non traversable tag, this position
            // is not able to be traversed
            if(t == "NON_TRAVERSABLE") { return false; }
        }
    }
    return true;
}

struct ColliderComponent: public Component
{

    ColliderComponent() {}
    
    ~ColliderComponent() {}

};