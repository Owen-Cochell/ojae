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
        name = "SpriteComponent";
        symbol = _symbol;
        color = _color;
        priority = _priority;
    }

    SpriteComponent(const SpriteComponent& c) : Component(c)
    {

        symbol = c.symbol;
        color = c.color;
        priority = c.priority;
    }

    ~SpriteComponent() {}

    void update() override {}
};
