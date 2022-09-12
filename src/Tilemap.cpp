#include <algorithm>

#include <fstream>

#include "Tilemap.h"

static std::fstream file_stream;

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
    text_funnel = nullptr;
    input_handler = nullptr;
    width = 0;
    height = 0;
    keep_tiles = false;
    keep_entities = false;
}

Tilemap::Tilemap(InputHandler* _input_handler, TextFunnel* _text_funnel,
    int _width, int _height)
{
    text_funnel = _text_funnel;
    input_handler = _input_handler;
    this->width = _width;
    this->height = _height;
    keep_tiles = false;
    keep_entities = false;
}

Tilemap::Tilemap(InputHandler* _input_handler, TextFunnel* _text_funnel, 
    Player* _player, int _width, int _height)
{
    text_funnel = _text_funnel;
    input_handler = _input_handler;
    width = _width;
    height = _height;
    player = _player;
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

void Tilemap::handle_keys()
{
    for(Key* key : input_handler->get_active_keys())
    {
        switch(key->id)
        {
            // // w
            // case 119:

            //     move(player, player->get_x(), player->get_y() - 1);
            //     input_handler->set_delay(i);
            //     break;

            // // s
            // case 115:
                
            //     move(player, player->get_x(), player->get_y() + 1);
            //     input_handler->set_delay(i);
            //     break;

            // // d
            // case 100:

            //     move(player, player->get_x() + 1, player->get_y());
            //     input_handler->set_delay(i);
            //     break;

            // // a
            // case 97:

            //     move(player, player->get_x() - 1, player->get_y());
            //     input_handler->set_delay(i);
            //     break;

            // UP ARROW KEY 
            case SDLK_UP:
                
                move(player, player->get_x(), player->get_y() - 1);
                input_handler->set_delay(key->id);
                break;

            // Right ARROW KEY
            case SDLK_RIGHT:

                move(player, player->get_x() + 1, player->get_y());
                input_handler->set_delay(key->id);
                break;
            
            // DOWN ARROW KEY
            case SDLK_DOWN:
                
                move(player, player->get_x(), player->get_y() + 1);
                input_handler->set_delay(key->id);
                break;

            // LEFT ARROW KEY 
            case SDLK_LEFT:

                move(player, player->get_x() - 1, player->get_y());
                input_handler->set_delay(key->id);
                break;


            // 1 (Keypad)
            case 1073741913:

                move(player, player->get_x() - 1, player->get_y() + 1);
                input_handler->set_delay(key->id);
                break;
            
            // 2 (Keypad)
            case 1073741914:

                move(player, player->get_x(), player->get_y() + 1);
                input_handler->set_delay(key->id);
                break;
            
            // 3 (Keypad)
            case 1073741915:

                move(player, player->get_x() + 1, player->get_y() + 1);
                input_handler->set_delay(key->id);
                break;
            
            // 4 (Keypad)
            case 1073741916:

                move(player, player->get_x() - 1, player->get_y());
                input_handler->set_delay(key->id);
                break;

            // 5 (Keypad)
            case 1073741917:

                move(player, player->get_x(), player->get_y() + 1);
                input_handler->set_delay(key->id);
                break;
            
            // 6 (Keypad)
            case 1073741918:

                move(player, player->get_x() + 1, player->get_y());
               input_handler->set_delay(key->id);
                break;
            
            // 7 (Keypad)
            case 1073741919:

                move(player, player->get_x() - 1, player->get_y() - 1);
                input_handler->set_delay(key->id);
                break;
            
            // 8 (Keypad)
            case 1073741920:

                move(player, player->get_x(), player->get_y() - 1);
                input_handler->set_delay(key->id);
                break;
            
            // 9 (Keypad)
            case 1073741921:

                move(player, player->get_x() + 1, player->get_y() - 1);
                input_handler->set_delay(key->id);
                break;       
        }
    }
}

void Tilemap::update_all_entities() {}

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

void Tilemap::move(Tile* tile, int x, int y) 
{
    remove(tile);
    add(tile, x, y);
}

void Tilemap::move(Entity* entity, int x, int y)
{
    /*
    Attemps to move an entity to the passed coordinates. This function adds
    the x_amount and y_amount to the entity's coordinates rather than moveing
    this entity to a specified coordinate

    :PARAM entity: Entity to move
    :PARAM x_amount: X amount to add to coordinate
    :PARAM y_amount: Y amount to add to coordinate
    */

    // If the new spot is out of bounds, we do not want to move this entity
    if(!bound_check(x, y))
    {
        return;
    }

    // Loop through the tiles at this position and check if there are any 
    // non traversable tiles
    for(Tile* tile : tiles[{x, y}])
    {

        if(tile->is_interactable())
        {
            tile->interact();
        }

        if(!tile->is_traversable())
        {
            return;
        }
    }

    // Check if there is an entity at this location
    if(entities.count({x, y}) != 0)
    {
        // Loop through the entities at this position and check if there are any 
            // non traversable entities

        for(Entity* entity : entities[{x, y}])
        {
            if(!entity->is_traversable())
            {
                return;
            }
        }
    }

    remove(entity);
    add(entity, x, y);
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

void Tilemap::move_all_entities() {}

