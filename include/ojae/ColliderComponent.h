#pragma once 

#include "ECS.h"

static bool bound_check(std::vector<Entity*> entities)
{
    // Iterate through the entities 
    for(Entity* targ_e : entities)
    {
        // Iterate through the tags of each entity
        for(std::string t : targ_e->tags)
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
    std::vector<std::string> exceptions; // Vector of 'tag' instances, where
        // if any entity contains a tag that is present in this vector, it 
        // will be allowed to traverse over the entity with this component

    ColliderComponent() {}

    ColliderComponent(std::vector<std::string> _exceptions) 
    {
        exceptions = _exceptions;
    }
    
    ColliderComponent(const ColliderComponent& c) : Component(c) {}

    ~ColliderComponent() {}

    /**
     * @brief Called when an entity attempts to move over the same space 
     * where this component is present. Returns whether the entity 
     * attempting to move here is allowed to do so based on its tags
     * 
     * @param e Entity colliding with this component
     * @return true if the entity can move
     */
    bool collide(Entity* e)
    {
        // Iterate through the target entity's tags
        for(std::string targ_t : e->tags)
        {
            // Iterate through the exception tags inside this component
            for(std::string t : exceptions)
            {
                // If this entity contains a tag that is an exception to 
                // this collider, allow it to traverse over this component
                if(targ_t == t) { return true; }
            }
        }

        return false;
    }
};