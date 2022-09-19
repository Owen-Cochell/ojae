#pragma once

#include <string>
#include <vector>
#include <map>

#include "Tile.h"
#include "Entity.h"
#include "Item.h"
#include "Player.h"
#include "Character.h"

class Tilemap
{

private:

    TileManager* tile_manager; // Instance of the TileManager
    EntityManager* entity_manager; // Instance of the EntityManager

    std::vector<Character*> display; // Stores the top priority characters for 
        // rendering our tilemap

    int width; // Width of the tilemap
    int height; // Height of the tilemap

    Player* player; // Instance of the Player

    InputHandler* input_handler; // Instance of the InputHandler

    TextFunnel* text_funnel; // Instance of the TextFunnel

public:

    bool keep_tiles; // If the tilemap keeps the tiles in heap memory when deleted
    bool keep_entities;// If the tilemap keeps the entities in heap memory when deleted

    Tilemap();
    // Tilemap(int width, int height);
    Tilemap(InputHandler* _input_handler, TextFunnel* _text_funnel, 
        Debugger* _debugger, int _width, int _height);
    // Tilemap(Player* player, int width, int height);
    Tilemap(InputHandler* _input_handler, TextFunnel* _text_funnel,
        Debugger* _debugger, Player* _player, int _width, int _height);
    ~Tilemap();

    std::vector<Character*> get_display();

    // bool bound_check(int x, int y);

    // void handle_keys();
    // void update_all_entities();
    void fill_tilemap(Tile* tile);
    void assemble_tilemap();
    void add(Tile* t, int x, int y);
    void add(Entity* e, int x, int y);
    // void move(Tile* tile, int x, int y);
    // void move(Entity* entity, int x, int y);
    // void remove(Tile* tile, bool deconstruct = false);
    // void remove(Entity* entity, bool deconstruct = false);
    void move_all_entities();
};