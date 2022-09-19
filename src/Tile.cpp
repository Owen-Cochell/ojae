#include <algorithm>

#include "Tile.h"

// Constructors/Deconstructors

TileManager::TileManager() {}

TileManager::TileManager(Debugger* _debugger, int _width, int _height)
{
    debugger = _debugger;
    width = _width;
    height = _height;
}

TileManager::~TileManager() {}

// Public Members

std::map<std::pair<int,int>, std::vector<Tile*>> 
    TileManager::get_tiles()
{
    return tiles;
}

bool TileManager::bound_check(int x, int y)
{
    if(x < 0 || x >= width || y < 0 || y >= height) { return false; }

    return true;
}

void TileManager::add_tile(Tile* t, int x, int y)
{
    // If the Tile's placement position is outside boundaries
    if(!bound_check(x, y))
    {
        debugger->log("[FAIL] TileManager.add_Tile() -> attempting to add "
            "Tile out of bounds: ", true, false);
        debugger->log( t->get_name(), false, false);
        debugger->log(" at (", false, false);
        debugger->log( t->get_x(), false, false);
        debugger->log(", ", false, false);
        debugger->log( t->get_y(), false, false);
        debugger->log(")");
        debugger->log("[OUT] Exiting...");
        exit(0);
    }

    // If this pair does not exists in the map
    if(tiles.count(std::pair<int,int>{x, y}) == 0)
    {
        tiles.emplace(std::pair<int,int>{x, y}, std::vector<Tile*>{});
    }

    tiles[{x, y}].push_back(t);
     t->set_position(x, y);
     t->set_tile_manager(this);
    std::sort(tiles[{x,y}].begin(), tiles[{x,y}].end(), tile_greater_priority());
}

void TileManager::remove_tile(Tile* t, bool deconstruct)
{
    int x =  t->get_x();
    int y =  t->get_y();

    // The coordinates do not exist in the map
    if(tiles.count({x, y}) == 0)
    {
        debugger->log("[FAIL] TileManager.remove_Tile() -> attempting to "
            "remove Tile from an empty position: ", true, false);
        debugger->log( t->get_name(), false, false);
        debugger->log(" at (", false, false);
        debugger->log( t->get_x(), false, false);
        debugger->log(", ", false, false);
        debugger->log( t->get_y(), false, false);
        debugger->log(")");
        debugger->log("[OUT] Exiting...");
        exit(0);
    }
    
    // Iterate throught the vector of tiles at this position and check if it
    // matches the Tile to remove

    for(int i = 0; i < tiles[{x, y}].size(); i++)
    {
        // This is the Tile we are searching for
        if(tiles[{x, y}].at(i) == t)
        {
            if(deconstruct) { delete t; }
            tiles[{x, y}].erase(tiles[{x, y}].begin() + i);

            // No tiles are present at this map position
            if(tiles[{x, y}].size() == 0)
            {
                tiles.erase({x, y});
            }

            return;
        }
    }

    // Tile was not found
    debugger->log("[FAIL] TileManager.remove_Tile() -> Tile was not"
            "found at specified position: ", true, false);
    debugger->log( t->get_name(), false, false);
    debugger->log(" at (", false, false);
    debugger->log( t->get_x(), false, false);
    debugger->log(", ", false, false);
    debugger->log( t->get_y(), false, false);
    debugger->log(")");
    debugger->log("[OUT] Exiting...");
    exit(0);

}

void TileManager::move_tile(Tile* t, int x, int y)
{
    // This position is out of bounds
    if(!bound_check(x, y))
    {
        return;
    }

    remove_tile(t);
    add_tile(t, x, y);
} 
