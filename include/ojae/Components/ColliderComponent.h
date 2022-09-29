#pragma once 

#include "../ECS.h"


struct ColliderComponent: public Component
{
    std::vector<std::string> exceptions; // Vector of 'tag' instances, where
        // if any entity contains a tag that is present in this vector, it 
        // will be allowed to traverse over the entity with this component

    ColliderComponent() 
    {
        name = "ColliderComponent";
    }

    ColliderComponent(std::vector<std::string> _exceptions) 
    {
        name = "ColliderComponent";
        exceptions = _exceptions;
    }

    Component* clone() override
    {
        return new ColliderComponent(exceptions);
    }
    
    // ColliderComponent(const ColliderComponent& c) : Component(c) 
    // {
    //     exceptions = c.exceptions;
    // }

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