#include <algorithm>

#include "InputHandler.h"

std::vector<char> InputHandler::keys {};

InputHandler::InputHandler() {}
InputHandler::~InputHandler() {}

void InputHandler::set_keys(std::vector<char> new_keys)
{
    keys = new_keys;
}

void InputHandler::add_key(char key)
{
    //If we did not find the key present in keys 
    if(std::find(keys.begin(), keys.end(), key) == keys.end())
    {
        keys.push_back(key);
    }
}

void InputHandler::remove_key(char key)
{
    keys.erase(std::remove(keys.begin(), keys.end(), key), keys.end());
}

std::vector<char> InputHandler::get_active_keys() { return keys; };