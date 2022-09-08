#pragma once

#include "Tile.h"

class InteractableObject : public Tile
{

private:


public:

    InteractableObject();
    InteractableObject(std::string _name, char _character, bool _traversable, 
        int _priority);
    ~InteractableObject();

    virtual void interact();
};