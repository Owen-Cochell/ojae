#pragma once

#include <string>

#include "ECS.h"

struct SpriteComponent : public Component
{
    char symbol;
    std::string color;
    int priority;

    SpriteComponent() {}
    
    SpriteComponent(char _symbol, std::string _color, int _priority) 
    {
        symbol = _symbol;
        color = _color;
        priority = _priority;
    }

    void update() override {}
};
