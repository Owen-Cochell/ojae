#pragma once

#include <string>
#include <vector>
#include <map>

#include "Tile.h"
#include "Entity.h"
#include "Item.h"

class Tilemap
{

private:

    std::map<std::pair<int,int>, std::vector<Tile*>> tiles; // List of tiles to their 
        // coordinates
    std::map<std::pair<int,int>, std::vector<Entity*>> entities; // List of entities to
        // their coordinates

    std::map<std::pair<int,int>, std::vector<Item*>> items; // List of tiles to
        // their coordinates

    std::map<std::pair<int, int>, char> display; // Stores the top priority
        // character per each coordinate marker

    int width; // Width of the tilemap
    int height; // Height of the tliemap

public:

    bool keep_tiles; // If the tilemap keeps the tiles in heap memory when deleted
    bool keep_entities;// If the tilemap keeps the entities in heap memory when deleted
    bool keep_items;// If the tilemap keeps the items in heap memory when deleted

    Tilemap();
    Tilemap(int width, int height);
    ~Tilemap();

    std::map<std::pair<int, int>, char> get_display();

    void fill_tilemap(Tile* tile);
    void assemble_tilemap();
    void add(Tile* tile, int x, int y);
    void add(Entity* entity, int x, int y);
    void add(Item* item, int x, int y);
    void remove(Tile* tile, bool deconstruct = false);
    void remove(Entity* tile, bool deconstruct = false);
    void remove(Item* tile, bool deconstruct = false);
};