#pragma once

// https://www.youtube.com/watch?v=XsvI8Sng6dk&t=1042s Not a complete copy,
// but used this for reference.

#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <map>
#include <string>

#include "Character.h"

struct Component;
struct Entity;

using ComponentID = std::size_t;

inline ComponentID get_component_type_id()
{
    static ComponentID lastID = 0;
    return lastID++;
}

template<typename T> inline ComponentID get_component_type_id() noexcept
{
    static ComponentID typeID = get_component_type_id();
    return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

struct Component
{
    Entity* entity;
    std::string name;

    Component() {}

    Component(const Component& c)
    {
        name = c.name;
    }

    virtual Component* clone() {}

    virtual ~Component() {}

};

/**
 * @brief Modular class for atatching behavior to entities
 */
struct Script
{
    std::string name;
    Entity* entity;

    Script() 
    {
        start();
    }

    Script(const Script& s)
    {
        name = s.name;
    }

    virtual Script* clone() {}

    virtual ~Script() {}

    /**
     * @brief Called when the object is created 
     */
    virtual void start() {}

    /**
     * @brief Called once per frame
     * 
     */
    virtual void update() {}
};

class EntityHandler;

struct Entity
{

    std::string name; 
    std::vector<std::string> tags;

    std::vector<Component*> components;
    std::map<std::string, Script*> scripts;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;

    EntityHandler* entity_handler;

    Entity() 
    {
        for(int i = 0; i < componentArray.size(); i++)
        {
            componentArray[i] = nullptr;
        }
    }
    
    Entity(std::string _name)
    {
        name = _name;
        for(int i = 0; i < componentArray.size(); i++)
        {
            componentArray[i] = nullptr;
        }
    }

    ~Entity() 
    {
        for(Component* c : components)
        {
            delete c;
        }

        for(std::map<std::string, Script*>::iterator it = scripts.begin(); 
            it != scripts.end(); it++)
        {
            delete it->second;
        }

        scripts.clear();
    }

    void update()
    {
        for(std::map<std::string, Script*>::iterator it = scripts.begin(); 
            it != scripts.end(); it++)
        {
            it->second->update();
        }
    }

    void add_script(Script* s)
    {
        scripts[s->name] = s;
        s->entity = this;
    }

    bool remove_script(Script* s)
    {
        if(scripts.count(s->name) == 0)
        {
            return false;
        }

        scripts.erase(s->name);
        return true;
    }

    void add_tag(std::string tag)
    {
        tags.push_back(tag);
    }

    bool remove_tag(std::string tag)
    {
        for(int i = 0; i < tags.size(); i++)
        {
            if(tags.at(i) == tag)
            {
                tags.erase(tags.begin() + i);
                return true;
            }
        }

        return false;
    }

    template <typename T> bool has_component() const
    {
        return componentBitSet[get_component_type_id<T>()];
    }

    template <typename T, typename... TArgs>
    T& add_component(TArgs&&... mArgs)
    {
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        components.emplace_back(c);

        componentArray[get_component_type_id<T>()] = c;
        componentBitSet[get_component_type_id<T>()] = true;

        // c->init();
        return *c;
    }

    Script* get_script(std::string script_name)
    {
        if(scripts.count(script_name) == 0)
        {
            return nullptr;
        }

        return scripts[script_name];
    }

    template <typename T> T* get_component() const 
    {
        return static_cast<T*>(componentArray[get_component_type_id<T>()]);
    }
};

class EntityHandler
{

private:

    // std::vector<Entity*> entities;
    std::map<std::pair<int, int>, std::vector<Entity*>> entity_positions;

    int width;
    int height;

public:

    EntityHandler() {}

    ~EntityHandler() {}

    void update()
    {

        for(std::map<std::pair<int, int>, std::vector<Entity*>>::iterator it =
            entity_positions.begin(); it != entity_positions.end(); it++ ) 
        {
            
            for(Entity* e : it->second) e->update();
        }
    }
        
    std::map<std::pair<int, int>, std::vector<Entity*>> get_entity_positions()
    {
        return entity_positions;
    }

    void add_entity(Entity* e, int x, int y)
    {
        e->entity_handler = this;
        entity_positions[{x, y}].push_back(e);
    }

    bool remove_entity(Entity* e, int x, int y)
    {

        for(int i = 0; i < entity_positions[{x, y}].size(); i++)
        {
            if(entity_positions[{x, y}].at(i) == e)
            {
                entity_positions[{x, y}].erase(
                    entity_positions[{x, y}].begin() + i);
                return true;
            }
        }
        return false;
    }
};
