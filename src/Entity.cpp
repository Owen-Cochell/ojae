#include <algorithm>

#include "Entity.h"

// Entity ---------------------------------------------------------------------

Entity::Entity() : Tile() {}

Entity::Entity(std::string name, std::string color, char character, int priority) :
        Tile(name, color, character, false, priority) {}

Entity::~Entity() {}

void Entity::update() {}

void Entity::set_entity_manager(EntityManager* _entity_manager)
{
    entity_manager = _entity_manager;
}


// EntityManager --------------------------------------------------------------

// Constructors/Deconstructors

EntityManager::EntityManager() {}

EntityManager::EntityManager(Debugger* _debugger, int _width, int _height)
{
    debugger = _debugger;
    width = _width;
    height = _height;
}

EntityManager::~EntityManager() {}

// Private Members


// Public Members

std::map<std::pair<int,int>, std::vector<Entity*>> 
    EntityManager::get_entities()
{
    return entities;
}

bool EntityManager::bound_check(int x, int y)
{
    if(x < 0 || x >= width || y < 0 || y >= height) { return false; }

    return true;
}

void EntityManager::add_entity(Entity* e, int x, int y)
{
    // If the entity's placement position is outside boundaries
    if(!bound_check(x, y))
    {
        debugger->log("[FAIL] EntityManager.add_entity() -> attempting to add "
            "entity out of bounds: ", true, false);
        debugger->log(e->get_name(), false, false);
        debugger->log(" at (", false, false);
        debugger->log(e->get_x(), false, false);
        debugger->log(", ", false, false);
        debugger->log(e->get_y(), false, false);
        debugger->log(")");
        debugger->log("[OUT] Exiting...");
        exit(0);
    }

    // If this pair does not exists in the map
    if(entities.count(std::pair<int,int>{x, y}) == 0)
    {
        entities.emplace(std::pair<int,int>{x, y}, std::vector<Entity*>{});
    }

    entities[{x, y}].push_back(e);
    e->set_position(x, y);
    e->set_entity_manager(this);
    std::sort(entities[{x,y}].begin(), entities[{x,y}].end(), entity_greater_priority());
}

void EntityManager::remove_entity(Entity* e, bool deconstruct)
{
    int x = e->get_x();
    int y = e->get_y();

    // The coordinates do not exist in the map
    if(entities.count({x, y}) == 0)
    {
        debugger->log("[FAIL] EntityManager.remove_entity() -> attempting to "
            "remove entity from an empty position: ", true, false);
        debugger->log(e->get_name(), false, false);
        debugger->log(" at (", false, false);
        debugger->log(e->get_x(), false, false);
        debugger->log(", ", false, false);
        debugger->log(e->get_y(), false, false);
        debugger->log(")");
        debugger->log("[OUT] Exiting...");
        exit(0);
    }
    
    // Iterate throught the vector of entities at this position and check if it
    // matches the entity to remove

    for(int i = 0; i < entities[{x, y}].size(); i++)
    {
        // This is the entity we are searching for
        if(entities[{x, y}].at(i) == e)
        {
            if(deconstruct) { delete e; }
            entities[{x, y}].erase(entities[{x, y}].begin() + i);

            // No entities are present at this map position
            if(entities[{x, y}].size() == 0)
            {
                entities.erase({x, y});
            }

            return;
        }
    }

    // Entity was not found
    debugger->log("[FAIL] EntityManager.remove_entity() -> Entity was not"
            "found at specified position: ", true, false);
    debugger->log(e->get_name(), false, false);
    debugger->log(" at (", false, false);
    debugger->log(e->get_x(), false, false);
    debugger->log(", ", false, false);
    debugger->log(e->get_y(), false, false);
    debugger->log(")");
    debugger->log("[OUT] Exiting...");
    exit(0);

}

void EntityManager::move_entity(Entity* e, int x, int y)
{
    // This position is out of bounds
    if(!bound_check(x, y))
    {
        return;
    }

    std::vector<Tile*> interactable_tiles;
    bool non_traversable_found = false;

    remove_entity(e);
    add_entity(e, x, y);
} 


// Owen -----------------------------------------------------------------------

// void MovementEntity::calc_move() {
    
//     // Determine the delta time:

//     uint64_t delta = (SDL_GetPerformanceCounter() - this->last) / this->freq;

//     // Determine the new velocity::

//     this->x_vel += x_acc * delta;
//     this->y_vel += y_acc * delta;

//     // Determine the new position:

//     this->x_pos += x_vel * delta;
//     this->y_pos += y_vel * delta;
// }
