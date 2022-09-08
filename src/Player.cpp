#include "Player.h"

Player::Player() 
{
    input_handler = nullptr;
    text_funnel = nullptr;
}

Player::Player(InputHandler* _input_handler, TextFunnel* _text_funnel, 
    std::string _name, char _character) : Entity(_name, _character, 20) 
{
    input_handler = _input_handler;
    text_funnel = _text_funnel;
}

Player::~Player() {}

