#pragma once

#include <map>
#include <vector>

#include "ECS.h"
#include "Debugger.h"

class Tilemap
{

private:

    EntityHandler* entity_handler;
    std::vector<Character*> display;

    Debugger* debugger;

    int width; 
    int height;

public:

    Tilemap();
    Tilemap(Debugger* _debugger, int _width, int _height);
    ~Tilemap();

    std::vector<Character*> get_display();

    void update();
    void add_entity(Entity* e, int x, int y);
    void remove_entity(Entity* e);
    void fill_tilemap(Entity* e);
};