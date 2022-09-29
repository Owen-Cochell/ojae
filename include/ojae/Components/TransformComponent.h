#pragma once

#include "../ECS.h"

struct TransformComponent : public Component
{

    int x_pos;
    int y_pos;


    TransformComponent() 
    {
        name = "TransformComponent";
        x_pos = 0;
        y_pos = 0;
    }

    TransformComponent(int x, int y)
    {
        name = "TransformComponent";
        x_pos = x;
        y_pos = y;
    }

    Component* clone() override
    {
        return new TransformComponent(x_pos, y_pos);
    }

    ~TransformComponent() {}

    void set_position(int x, int y)
    {
        x_pos = x;
        y_pos = y;
    }
};
