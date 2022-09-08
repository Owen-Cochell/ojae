#include "InteractableObject.h"


InteractableObject::InteractableObject() : Tile() {}

InteractableObject::InteractableObject(std::string _name, char _character,
    bool _traversable, int _priority) : 
    Tile(_name, _character, _traversable, _priority) {}

InteractableObject::~InteractableObject() {}


