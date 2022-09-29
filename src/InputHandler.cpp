#include <algorithm>
#include <stdexcept>
#include <iostream>

#include "InputHandler.h"

SDL_Event event;

InputHandler::InputHandler() {}
InputHandler::~InputHandler() {}

void InputHandler::update() 
{

    // Iterate through each Key and deduct 1 frame from its delay
    for(std::map<int,Key*>::iterator it = keys.begin(); it != keys.end(); it++)
    {

        it->second->frames_delay -= 1;
        if(it->second->frames_delay <= 0)
        {
            // remove_key(it->first);
            it->second->frames_delay = 0;
        }
    }
}

void InputHandler::set_delay(int i, int frames) 
{
    if(keys.count(i) != 0)
    {   
        keys[i]->frames_delay = frames;
    }
}

void InputHandler::add_key(int key) 
{
    if(keys.count(key) == 0)
    {
        keys[key] = new Key(key);
    }
}

void InputHandler::remove_key(int key) 
{
    if(keys.count(key) != 0)
    {
        delete keys[key];
        keys.erase(key);
    }
}

std::vector<Key*> InputHandler::get_active_keys() 
{
    std::vector<Key*> available_keys;

    for(std::map<int, Key*>::iterator it = keys.begin(); it != keys.end(); 
        it++)
    {
        if(it->second->frames_delay == 0)
        {
            available_keys.push_back(it->second);
        }
    }

    return available_keys;
}


// Owen 
//---------------------------------------------------------


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
