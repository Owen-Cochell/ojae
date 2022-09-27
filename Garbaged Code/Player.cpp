#include "Player.h"

// Constructors/Deconstructors

Player::Player() 
{
    input_handler = nullptr;
    text_funnel = nullptr;
}

Player::Player(InputHandler* _input_handler, TextFunnel* _text_funnel, 
    std::string _name, char _character) : Entity(_name, "Blue", _character, 20) 
{
    input_handler = _input_handler;
    text_funnel = _text_funnel;
}

Player::~Player() {}

// Public Members

void Player::handle_keys()
{
    for(Key* k: input_handler->get_active_keys())
    {
        switch(k->id)
        {
            // Up Arrow
            case SDLK_UP:

                entity_manager->move_entity(this, x_pos, y_pos - 1);
                input_handler->set_delay(k->id);
                break;
            
            // Up Arrow
            case SDLK_RIGHT:

                entity_manager->move_entity(this, x_pos + 1, y_pos);
                input_handler->set_delay(k->id);
                break;
            
            // Up Arrow
            case SDLK_DOWN:

                entity_manager->move_entity(this, x_pos, y_pos + 1);
                input_handler->set_delay(k->id);
                break;
            
            // Up Arrow
            case SDLK_LEFT:

                entity_manager->move_entity(this, x_pos - 1, y_pos);
                input_handler->set_delay(k->id);
                break;
        }
    }
}
