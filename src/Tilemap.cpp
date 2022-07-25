#include <algorithm>
#include <iostream>

#include "Tilemap.h"

Tilemap::Tilemap() 
{
    width = 0;
    height = 0;
    keep_tiles = false;
    keep_entities = false;
    keep_items = false;
}

Tilemap::Tilemap(int width, int height)
{
    this->width = width;
    this->height = height;
    keep_items = false;
    keep_entities = false;
    keep_items = false;
}

Tilemap::~Tilemap() {}

std::map<std::pair<int, int>, char> Tilemap::get_display() { return display; }

void Tilemap::fill_tilemap(Tile* tile)
{
    /*
    Fills the tilemap with a tile, creating new copies of each tile

    :PARAM tile: Tile to fill the tilemap with
    */

    int x = 0;
    int y = 0;

    // if(width > 0 && height > 0)
    // {
    //     // Place the tile that was passed as a parameter as the first tile 
    //     // in the map, so that the new tile that had to be created to be 
    //     // passed into the function does not sit useless in heap memory
        
    //     std::cout << "0, 0\n";
    //     tiles[{0,0}].push_back(tile);
    //     tile->set_position(0, 0);
    //     x++;
    //     y++;
        
    // }

    while(y < height)
    {
        x = 0;

        while(x < width)
        {

            Tile* new_tile = new Tile(*tile);
            tiles[{x,y}].push_back(new_tile);

            new_tile->set_position(x, y); 
            x++;
        }

        y++;
    }

    return;

}

void Tilemap::assemble_tilemap()
{
    /*
    Creates a visual representation of the highest priority characters of 
    the three vector types, being tiles, entities and items. This is used to 
    render them to the screen. 
    */
    
    // Clear all data in the display map
    display.clear();

    // Loop through tiles and add the first character in each vector to the display
    for(std::map<std::pair<int,int>, std::vector<Tile*>>::iterator
        it = tiles.begin(); it != tiles.end(); it++)
    {
        // There is at least one tile inside the vector at this coordinate point
        if(it->second.size() > 0)
        {
            // Set the display key at these coordinates to the highest priority 
            // character in the vector of tiles
            display[it->first] = it->second.at(0)->get_character();
        }
    }
}

void Tilemap::add(Tile* tile, int x, int y)
{
    /*
    Adds a tile at the specified coordinate point
    */

    tiles[{x,y}].push_back(tile);
}

void Tilemap::add(Entity* entity, int x, int y)
{
    /*
    Adds an entity at the specified coordinate point
    */

    entities[{x,y}].push_back(entity);
}

void Tilemap::add(Item* item, int x, int y)
{
    /*
    Adds an item at the specified coordinate point
    */

    items[{x,y}].push_back(item);
}

void Tilemap::remove(Tile* tile, bool deconstruct)
{
    /*
    Removes the tile from the tilemap, and if deconstruct is true, deletes 
    the object from heap memory

    :PARAM tile: Tile to remove
    :PARAM deconstruct: If it should delete the tile
    */

    tiles[{tile->get_x(), tile->get_y()}].erase(
        std::find(tiles[{tile->get_x(), tile->get_y()}].begin(), 
        tiles[{tile->get_x(), tile->get_y()}].end(), tile));

    if(deconstruct)
    {
        delete tile;
    }
}

void Tilemap::remove(Entity* entity, bool deconstruct)
{
    /*
    Removes the entity from the tilemap, and if deconstruct is true, deletes 
    the object from heap memory

    :PARAM entity: Entity to remove
    :PARAM deconstruct: If it should delete the entity
    */

    entities[{entity->get_x(), entity->get_y()}].erase(
        std::find(entities[{entity->get_x(), entity->get_y()}].begin(), 
        entities[{entity->get_x(), entity->get_y()}].end(), entity));

    if(deconstruct)
    {
        delete entity;
    }
}

void Tilemap::remove(Item* item, bool deconstruct)
{
    /*
    Removes the item from the tilemap, and if deconstruct is true, deletes 
    the object from heap memory

    :PARAM item: Item to remove
    :PARAM deconstruct: If it should delete the item
    */

    items[{item->get_x(), item->get_y()}].erase(
        std::find(items[{item->get_x(), item->get_y()}].begin(), 
        items[{item->get_x(), item->get_y()}].end(), item));

    if(deconstruct)
    {
        delete item;
    }
}

