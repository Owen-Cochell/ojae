#pragma once

#include <fstream>
#include <nlohmann/json.hpp>

#include "Tilemap.h"
#include "Jloader.h"
#include "Debug.h"

/**
 * @brief Handles loading and dumping tilemaps to json files
 * 
 */
class TilemapLoader
{

private:

    static std::fstream file_stream; // Instance of the fstream

public:


    /**
     * @brief Loads a tilemap from a json file
     * 
     * @param path Path to target file
     * @return A new Tilemap constructed from the parameters from the file
     */
    static Tilemap* load_tilemap(const char* path)
    {
        Tilemap* tilemap = nullptr;

        if(!Debug::file_exists(path))
        {
            Debug::log("[ERR] TilemapLoader.load_tilemap -> Could not open "
                "file: ", false, true);
            Debug::log(path, false, false);
            exit(0);
        }

        nlohmann::json j_loader = Jloader::get(path);

        for(nlohmann::json::iterator it = j_loader.begin(); 
            it != j_loader.end(); it++)
        {
            
        }

        return tilemap;
    }

    static void dump_tilemap(const Tilemap& t)
    {

    }

};