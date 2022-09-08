#include <algorithm>
#include <stdexcept>
#include <iostream>

#include "InputHandler.h"

std::vector<int> InputHandler::keys;
std::map<int, Uint64> InputHandler::keys_delay;

SDL_Event event;

InputHandler::InputHandler() {}
InputHandler::~InputHandler() {}

void InputHandler::update()
{
    /*
    Called once per frame. Checks if any key equals or exceed its timestamp
    for a delayed input. If so, it removes the key from the delayed map
    */

    Uint64 current_time = SDL_GetTicks64();

    std::vector<int> keys_to_delete;

    for(std::map<int,Uint64>::iterator it = keys_delay.begin();
        it != keys_delay.end(); it++)
    {
        if(it->second <= current_time)
        {
            keys_to_delete.push_back(it->first);
        }
    }

    for(int i : keys_to_delete)
    {
        keys_delay.erase(i);
    }
}

void InputHandler::set_delay(int i, int miliseconds)
{
    /*
    Sets the timestamp for delayed input for the specified character

    :PARAM c: Target Character
    :PARAM miliseconds: Number of miliseconds 
    */

    keys_delay[i] = SDL_GetTicks64() + miliseconds;
}

void InputHandler::add_key(int key)
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

void InputHandler::remove_key(int key)
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

std::vector<int> InputHandler::get_active_keys() 
{ 
    /*
    Loops through the vector of actively pressed keys, and returns a vector 
    of active keys depending on if they do not have a frame delay attached to 
    them

    :RETURN: Keys that do not have a frame delay
    */

    std::vector<int> active_keys;

    for(int key: keys)
    {
        if(keys_delay.count(key) == 0)
        {
            active_keys.push_back(key);
        }
    }

    return active_keys; 
};

InputTemp::InputTemp() {}
InputTemp::~InputTemp() {}

KeyCallbacks::KeyCallbacks() {}
KeyCallbacks::~KeyCallbacks() {}

void CallbackCollection::handle_event(SDL_Event& event) {
    
    // Sends the given event though the handlers associated with it:

    // Get the key for the event:

    int key = this->extract_key(event);

    // Get the vector at the key:
 
    Callbacks calls;

    try {

        calls = this->callbacks.at(key);
    }
    catch (const std::out_of_range& oor) { 
        // No valid events, return:

        return;
    }

    // Iterate over each function and call it:

    for (long unsigned int i = 0; i < calls.size(); i++) {

        // Call the function:

        (calls.at(i))(event);

    };
}

void CallbackCollection::add_callback(int type, std::function<void(SDL_Event&)> func) {

    // Test to see if a pair exists already:

    try{

        Callbacks& thing = this->callbacks.at(type);

        thing.push_back(func);
    }
    catch (const std::out_of_range& oor) {

        // Create a new pair and add it:

        this->callbacks[type] = Callbacks {func};

        for (long unsigned int i = 0; i < this->callbacks.at(type).size(); i++) {
            std::cout << &this->callbacks.at(type).at(i) << std::endl;
        }

    }

}

void InputTemp::get_event() {
    // Gets events from SDL and handles them:

    while(SDL_PollEvent(&event)) {

        // Send each key though the callbacks:

        this->handle_event(event);

    }
}

int KeyCallbacks::extract_key(SDL_Event& event) {
    // Extracts the key of this event:

    std::cout << "Extracted key: " << event.key.keysym.sym << std::endl;

    return event.key.keysym.sym;
}
