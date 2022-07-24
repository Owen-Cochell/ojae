#include <algorithm>

#include "InputHandler.h"

std::vector<char> InputHandler::keys;
std::map<char, int> InputHandler::keys_delay;

InputHandler::InputHandler() {}
InputHandler::~InputHandler() {}

void InputHandler::update()
{
    /*
    Called once per frame. Reduces frame delay for all characters by 1 and 
    removes them from the delay map if they are equal to or less than 0
    */

    for(std::map<char, int>::iterator it = keys_delay.begin();
        it != keys_delay.end(); it++)
    {
        // Reduce the frame delay on this character by 1
        it->second--;

        // If the frame delay for this character is less than or equal to 0, 
        // remove it from the character delay map
        if(it->second <= 0)
        {
            keys_delay.erase(it->first);
        }
    }
}

void InputHandler::set_delay(char c, int frames)
{
    /*
    Sets the frame delay for the specified character. 

    :PARAM c: Target character to add delay
    :PARAM frames: Number of frames for delay
    */

    keys_delay[c] =  frames;
}

void InputHandler::add_key(char key)
{
    /*
    Adds a key to our vector of active keys if the keys is not already present
    in the vector

    :PARAM key: Key to add
    */

    //If we did not find the key present in keys 
    if(std::find(keys.begin(), keys.end(), key) == keys.end())
    {
        keys.push_back(key);
    }
}

void InputHandler::remove_key(char key)
{
    /*
    Removes a key from the vector of active keys if it exists. This will also
    remove the key from the vector of keys with input delay if it exists in the
    map

    :PARAM key: Key to remove
    */

    // If the user has stopped pressing the key, we want to remove the delay
    // from their next key press of this key so they can tap as fast as they 
    // want to input this key without being blocked by a delay
    if(keys_delay.count(key) != 0){
        keys_delay.erase(key);
    }

    keys.erase(std::remove(keys.begin(), keys.end(), key), keys.end());
}

std::vector<char> InputHandler::get_active_keys() 
{ 
    /*
    Loops through the vector of actively pressed keys, and returns a vector 
    of active keys depending on if they do not have a frame delay attached to 
    them

    :RETURN: Keys that do not have a frame delay
    */

    std::vector<char> active_keys;

    for(char key: keys)
    {
        if(keys_delay.count(key) == 0)
        {
            active_keys.push_back(key);
        }
    }

    return active_keys; 
};