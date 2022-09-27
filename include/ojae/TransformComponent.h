#pragma once

#include "ECS.h"

struct TransformComponent : public Component
{

    int x_pos;
    int y_pos;

    TransformComponent() 
    {
        x_pos = 0;
        y_pos = 0;
    }

    TransformComponent(int x, int y)
    {
        x_pos = x;
        y_pos = y;
    }

    ~TransformComponent() {}

    void update() override {}

    void set_position(int x, int y)
    {
        x_pos = x;
        y_pos = y;
    }
};
