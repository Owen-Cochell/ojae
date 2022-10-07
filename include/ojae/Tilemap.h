#pragma once

#include <map>
#include <vector>

#include "ECS.h"
#include "Debugger.h"
#include "Character.h"

class Tilemap
{

private:

    EntityHandler* entity_handler;
    std::vector<Character*> display;

    int width; 
    int height;

public:

    Tilemap();
    Tilemap(int _width, int _height);
    ~Tilemap();

    std::vector<Character*> get_display();

    void update();
    void add_entity(Entity* e, int x, int y);
    void add_copy_entity(const Entity& e, int x, int y);
    void remove_entity(Entity* e);
    void fill_tilemap(Entity* e);
};