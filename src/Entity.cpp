#include "Entity.h"

// Entity ---------------------------------------------------------------------
Entity::Entity() : Tile() {}

Entity::Entity(std::string name, std::string color, char character, int priority) :
        Tile(name, color, character, false, priority) {}

Entity::~Entity() {}

void Entity::update() {}


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

void EntityManager::add_entity(Entity* e, int x, int y)
{
    // If the entity's placement position is outside boundaries
    if(x < 0 || x > width || y < 0 || y > height)
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
