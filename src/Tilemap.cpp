#include <algorithm>
#include <iostream>
#include <iostream>

#include "Tilemap.h"

struct greater_priority
{
    inline bool operator()(Entity* a, Entity* b)
    {
        return a->get_priority() > b->get_priority();
    }

    inline bool operator()(Tile* a, Tile* b)
    {
        return a->get_priority() > b->get_priority();
    }
};

Tilemap::Tilemap() 
{
    width = 0;
    height = 0;
    keep_tiles = false;
    keep_entities = false;
}

Tilemap::Tilemap(int width, int height)
{
    this->width = width;
    this->height = height;
    keep_tiles = false;
    keep_entities = false;
}

Tilemap::~Tilemap() {}

std::vector<char> Tilemap::get_display() 
{
    assemble_tilemap();
    return display;
}

bool Tilemap::bound_check(int x, int y)
{
    /*
    Checks if the passed coordinate is inside the bounds of the tilemap
    :PARAM x: X Coordinate
    :PARAM y: Y Coordinate
    */

    return x >= 0 && x < width && y >= 0 && y < height;
}

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
    the tiles and entities. This is used to render them to the screen. 
    */

    display.clear();

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            // If there is an entity in this coordinate
            if(entities.count({x,y}) != 0)
            {

                // If it is an empty vector
                if(entities[{x,y}].size() == 0)
                {
                    // Remove it
                    entities.erase({x,y});

                    // Since there is no entity to worry about rendering, simply
                    // render the top priority tile

                    goto DISPLAY_HIGHEST_TILE;
                }

                // If the entity at this position has a higher rendering 
                // priority than the tile under it
                if(entities[{x,y}].at(0)->get_priority() >= 
                    tiles[{x,y}].at(0)->get_priority())
                {
                    display.push_back(entities[{x,y}].at(0)->get_character());
                    continue;
                }
            }

            DISPLAY_HIGHEST_TILE:

            display.push_back(tiles[{x,y}].at(0)->get_character());   
        }
    
        display.push_back('\n');
    }
}

void Tilemap::add(Tile* tile, int x, int y)
{
    /*
    Adds a tile at the specified coordinate point
    */

    tiles[{x,y}].push_back(tile);
    std::sort(tiles[{x,y}].begin(), tiles[{x,y}].end(), greater_priority());
    tile->set_position(x, y);
}

void Tilemap::add(Entity* entity, int x, int y)
{
    /*
    Adds an entity at the specified coordinate point
    */

    entities[{x,y}].push_back(entity);
    std::sort(entities[{x,y}].begin(), entities[{x,y}].end(), greater_priority());
    entity->set_position(x, y);
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

void Tilemap::move(Tile* tile, int x_amount, int y_amount) {}

void Tilemap::move(Entity* entity, int x_amount, int y_amount)
{
    /*
    Moves an entity in accordance to the passed paramteres. This function adds
    the x_amount and y_amount to the entity's coordinates rather than moveing
    this entity to a specified coordinate

    :PARAM entity: Entity to move
    :PARAM x_amount: X amount to add to coordinate
    :PARAM y_amount: Y amount to add to coordinate
    */

    // Calculate the spot the entity is trying to move to
    int targ_x = entity->get_x() + x_amount;
    int targ_y = entity->get_y() + y_amount;

    // If the new spot is out of bounds, we do not want to move this entity
    if(!bound_check(targ_x, targ_y))
    {
        return;
    }

    remove(entity);
    add(entity, targ_x, targ_y);
}
