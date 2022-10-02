#pragma once

#include "Debug.h"
#include "ECS.h"
#include "Components/Components.h"
#include "Scripts/Scripts.h"

struct EntityCopier
{
    /**
     * @brief Returns a deep copy of an entity
     * 
     * @param e Entity to copy
     * @return Entity* 
     */
    static Entity* copy_entity(const Entity& e)
    {

        Entity* new_entity = new Entity();

        // Name
        new_entity->name = e.name;

        // Tags
        for(std::string t : e.tags)
        {
            new_entity->add_tag(t);
        }

        // BitSet
        for(int i = 0; i < e.componentBitSet.size(); i++)
        {
            new_entity->componentBitSet[i] = e.componentBitSet[i];
        }

        // Components
        for(Component* c : e.components)
        {
            Component* new_component = c->clone();

            if(new_component == nullptr)
            {
                Debug::log("[FAIL] EntityCopier.copy_entity -> Attempted to copy a "
                    "component of type nullptr");
                Debug::log("[OUT] Exiting...");
                exit(0);
            }

            new_entity->components.push_back(new_component);
            new_component->entity = new_entity;

            // ComponentArray 
            for(int i = 0; i < e.componentArray.size(); i++)
            {
                if(e.componentArray[i] == nullptr) 
                {
                    continue; 
                }

                if(new_component->name == 
                    e.componentArray[i]->name)
                {
                    new_entity->componentArray[i] = new_component;
                }
            }
        }
        // Scripts
        for(std::map<std::string, Script*>::const_iterator it = e.scripts.begin();
            it != e.scripts.end(); it++)
        {
            new_entity->add_script(it->second->clone());
        }

        new_entity->entity_handler = e.entity_handler;

        return new_entity;
    }

};