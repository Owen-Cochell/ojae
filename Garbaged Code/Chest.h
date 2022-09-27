#pragma once

#include "../Tile.h"
#include "../TextFunnel.h"

class Chest : public Tile
{

private:

    TextFunnel* text_funnel; // Instance of the TextFunnel

public:

    Chest() : Tile() {}

    Chest(TextFunnel* _text_funnel) : Tile("Chest", "Brown", 'C', false, 5) 
    {
        text_funnel = _text_funnel;
        interactable = true;
    }

    ~Chest() {}

    void interact(Tile* tile) override
    {
        text_funnel->add("Opened Chest");
    }
};