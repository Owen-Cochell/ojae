#pragma once

#include "Entity.h"
#include "TextFunnel.h"
#include "InputHandler.h"


class Player : public Entity
{

private:

    TextFunnel* text_funnel;
    InputHandler* input_handler;

public:

    int x_velocity;
    int y_velocity;

    Player();
    Player(InputHandler* _input_handler, TextFunnel* _text_funnel, 
        std::string _name, char _character);
    ~Player();

    void update();
};