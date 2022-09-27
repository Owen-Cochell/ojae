#pragma once

#include <string>
#include <map>
#include <vector>

#include "Debugger.h"


class TileManager;

/**
 * @brief Basic character that can be added to a tilemap. Offers little 
 * functionality */
class Tile
{

    /*
    A 'Tile' is a texture on the screen.
    */

protected:

    TileManager* tile_manager; // Instance of the TileManager

    std::string name; // Name of the tile
    std::string color; // Color of the tile

    char character; // Visual character that is rendered

    int x_pos; // X Coordinate
    int y_pos; // Y Coordinate
    int priority; // Rendering priority of the Tile

    bool traversable; // If this tile is traversable by things that can move
    bool interactable; // If this tile is able to be interacted with

public:

    Tile()
    {   
        character = ' ';
        x_pos = 0;
        y_pos = 0;
        priority = 0;
        traversable = true;
        interactable = false;
    }

    Tile(std::string _name, std::string _color, char _character, 
        bool _traversable, int _priority)
    {
        name = _name;
        color = _color;
        character = _character;
        x_pos = 0;
        y_pos = 0;
        priority = _priority;
        traversable = _traversable;
        interactable = false;
    }

    virtual ~Tile() {}

    std::string get_name() { return name; }

    std::string get_color() { return color; }

    char get_character() { return character; }

    int get_x() { return x_pos; }

    int get_y() { return y_pos; }

    int get_priority() { return priority; }

    bool is_traversable() { return traversable; }

    bool is_interactable() { return interactable; }

    void set_position(int x, int y)
    {
        /*
        Sets new x and y coordinates for the tile

        :PARAM x: X Coordinate
        :PARAM y: Y Coordinate
        */

        x_pos = x;
        y_pos = y;
    }
    
    void set_tile_manager(TileManager* _tile_manager)
    {
        tile_manager = _tile_manager;
    }

    /**
     * @brief Called whenever a Tile attempts to move/interact with this 
     * tile
     * @param t Tile that is interacting 
     * */
    virtual void interact(Tile* t) {}
};

struct tile_greater_priority
{

    inline bool operator()(Tile* a, Tile* b)
    {
        return a->get_priority() > b->get_priority();
    }
};

class TileManager
{

private:

    Debugger* debugger; // Instance of the Debugger

    /**
     * @brief Map of coordinate positions to a vector of tiles
     */
    std::map<std::pair<int,int>, std::vector<Tile*>> tiles;

    int width; // Width in tiles limit for tile placement
    int height; // Height in tiles limit for tile placement

public:

    TileManager();
    TileManager(Debugger* _debugger, int _width, int _height);
    ~TileManager();

    std::map<std::pair<int,int>, std::vector<Tile*>> get_tiles();

    /**
     * @brief Checks if a coordinate point in the map is within the 
     * constrictions
     * 
     * @param x X Position
     * @param y Y Position
     * @return True if the spot is available to move to
     */
    bool bound_check(int x, int y);

    /**
     * @brief Adds a TIle to the map of tiles at a given position
     * 
     * @param t Tile to add
     */
    void add_tile(Tile* t, int x, int y);

    /**
     * @brief Removes a Tile from the map of Tiles. Uses the Tiles's 
     * current position to target which position to remove it from
     * 
     * @param t Tile to remove
     * @param deconstruct Remove the Tile from heap memory
     */
    void remove_tile(Tile* t, bool deconstruct = false);

    /**
     * @brief Moves a Tile to a new position in the map
     * 
     * @param t Tile to move
     * @param x X Position
     * @param y Y Position
     */
    void move_tile(Tile* t, int x, int y);

};
