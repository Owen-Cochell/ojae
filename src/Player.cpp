#include <iostream>

#include "Player.h"

Player::Player() 
{
    input_handler = nullptr;
    text_funnel = nullptr;

    x_velocity = 0;
    y_velocity = 0;
}

Player::Player(InputHandler* _input_handler, TextFunnel* _text_funnel, 
    std::string _name, char _character) : Entity(_name, _character, 20) 
{
    input_handler = _input_handler;
    text_funnel = _text_funnel;

    x_velocity = 0;
    y_velocity = 0;
}

Player::~Player() {}

void Player::update()
{
    /*
    Calculates the players velocity based on pressed keys
    */

    x_velocity = 0;
    y_velocity = 0;

    // Parse through the actively pressed keys 
    for(int i : input_handler->get_active_keys())
    {
        switch(i)
        {
            // w
            case 119:

                y_velocity = -1;
                input_handler->set_delay(i);
                break;

            // s
            case 115:
                
                y_velocity = 1;
                input_handler->set_delay(i);
                break;

            // d
            case 100:

                x_velocity = 1;
                input_handler->set_delay(i);
                break;

            // a
            case 97:

                x_velocity = -1;
                input_handler->set_delay(i);
                break;
        }
    }
}

