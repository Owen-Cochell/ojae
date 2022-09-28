#pragma once

#include "ECS.h"
#include "Components.h"

struct EntityCopier
{

static Entity* copy_entity(Entity* e)
{

    Entity* new_entity = new Entity();

    // Name
    new_entity->name = e->name;

    // Tags
    for(std::string t : e->tags)
    {
        new_entity->add_tag(t);
    }

    // BitSet
    for(int i = 0; i < e->componentBitSet.size(); i++)
    {
        new_entity->componentBitSet[i] = e->componentBitSet[i];
    }

    // Components
    for(Component* c : e->components)
    {
        Component* new_component = copy_component(*e, c->name);

        if(new_component == nullptr)
        {
            std::cout << "Non Valid Component\n";
            exit(0);
        }

        new_entity->components.push_back(new_component);
        new_component->entity = new_entity;

        // ComponentArray 
        for(int i = 0; i < e->componentArray.size(); i++)
        {
            if(e->componentArray[i] == nullptr) 
            {
                continue; 
            }

            if(new_component->name == 
                e->componentArray[i]->name)
            {
                new_entity->componentArray[i] = new_component;
            }
        }
    }

    new_entity->entity_handler = e->entity_handler;

    return new_entity;
}

static Component* copy_component(const Entity& e, std::string c_name)
{

    if(c_name == "ColliderComponent")
    {
        ColliderComponent* targ_c = e.get_component<ColliderComponent>();

        ColliderComponent* new_c = new ColliderComponent(*targ_c);
        return new_c;
    }

    else if(c_name == "InputComponent")
    {
        InputComponent* targ_c = e.get_component<InputComponent>();

        InputComponent* new_c = new InputComponent(*targ_c);
        return new_c;
    }

    else if(c_name == "SpriteComponent")
    {
        SpriteComponent* targ_c = e.get_component<SpriteComponent>();

        SpriteComponent* new_c = new SpriteComponent(*targ_c);
        return new_c;
    }

    else if(c_name == "TransformComponent")
    {
        TransformComponent* targ_c = e.get_component<TransformComponent>();

        TransformComponent* new_c = new TransformComponent(*targ_c);
        return new_c;
    }

    return nullptr;
}

};