#pragma once

#include "Entity.h"
#include "TextFunnel.h"
#include "InputHandler.h"

/**
 * @brief Player class that is represented by the user. Extends an Entity 
 * object to hold specific logic for the user
 * 
 */
class Player : public Entity
{

private:

    TextFunnel* text_funnel; // Instance of the TextFunnel
    InputHandler* input_handler; // Instance of the InputHandler

public:

    Player();
    Player(InputHandler* _input_handler, TextFunnel* _text_funnel, 
        std::string _name, char _character);
    ~Player();

    
};