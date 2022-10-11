#pragma once

#include <string>

#include "../ECS.h"

struct SpriteComponent : public Component
{
    char symbol;
    std::string color;
    int priority;
    
    SpriteComponent(char _symbol, std::string _color, int _priority) 
    {
        name = "SpriteComponent";
        symbol = _symbol;
        color = _color;
        priority = _priority;
    }

    Component* clone() override
    {
        return new SpriteComponent(symbol, color, priority);
    }
};
