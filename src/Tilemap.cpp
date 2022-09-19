#include <algorithm>

#include <fstream>

#include "Tilemap.h"

static std::fstream file_stream;

Tilemap::Tilemap() 
{
    text_funnel = nullptr;
    input_handler = nullptr;
    entity_manager = nullptr;
    tile_manager = nullptr;
    width = 0;
    height = 0;
    keep_tiles = false;
    keep_entities = false;
}

Tilemap::Tilemap(InputHandler* _input_handler, TextFunnel* _text_funnel,
    Debugger* _debugger, int _width, int _height)
{
    text_funnel = _text_funnel;
    input_handler = _input_handler;
    entity_manager = new EntityManager(_debugger, _width, _height);
    tile_manager = new TileManager(_debugger, _width, _height);
    this->width = _width;
    this->height = _height;
    keep_tiles = false;
    keep_entities = false;
}

Tilemap::Tilemap(InputHandler* _input_handler, TextFunnel* _text_funnel,
    Debugger* _debugger, Player* _player, int _width, int _height)
{
    text_funnel = _text_funnel;
    input_handler = _input_handler;
    entity_manager = new EntityManager(_debugger, _width, _height);
    tile_manager = new TileManager(_debugger, _width, _height);
    width = _width;
    height = _height;
    player = _player;
    keep_tiles = false;
    keep_entities = false;
}

Tilemap::~Tilemap() 
{
    delete entity_manager;
}

std::vector<Character*> Tilemap::get_display() 
{
    assemble_tilemap();
    return display;
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
            tile_manager->add_tile(new_tile, x, y);
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

    // Delete character objects so we don't have memory leaks
    for(Character* c : display)
    {
        delete c;
    }

    display.clear();

    std::map<std::pair<int,int>, std::vector<Entity*>> entities = 
        entity_manager->get_entities();

    std::map<std::pair<int,int>, std::vector<Tile*>> tiles = 
        tile_manager->get_tiles();

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            // If there is an entity in this coordinate
            if(entities.count({x,y}) != 0)
            {

                // If the entity at this position has a higher rendering 
                // priority than the tile under it
                if(entities[{x,y}].at(0)->get_priority() >= 
                    tiles[{x,y}].at(0)->get_priority())
                {
                    display.push_back(new Character
                        (entities[{x,y}].at(0)->get_character(), 
                        entities[{x,y}].at(0)->get_color(), 0, 0));
                    continue;
                }
            }

            display.push_back(new Character
                        (tiles[{x,y}].at(0)->get_character(), 
                        tiles[{x,y}].at(0)->get_color(), 0, 0));   
        }
    
        display.push_back(new Character('\n', "White", 0, 0));
    }
}

void Tilemap::add(Tile* t, int x, int y)
{

    tile_manager->add_tile(t, x, y);
}

void Tilemap::add(Entity* e, int x, int y)
{
    entity_manager->add_entity(e, x, y);
}

void Tilemap::move_all_entities() {}

