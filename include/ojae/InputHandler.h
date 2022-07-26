#pragma once

#include <vector>
#include <functional>
#include <map>

#include <SDL2/SDL.h>

class InputHandler
{

private:

    static std::vector<char> keys; // Keys that are currently active
    static std::map<char, int> keys_delay; // Frame delay before the keys will 
    // be allowed to be used again

public:

    InputHandler();
    ~InputHandler();

    void update();
    void set_delay(char c, int frames = 8);
    void add_key(char key);
    void remove_key(char key);

    std::vector<char> get_active_keys();

};

typedef std::vector<std::function<void(SDL_Event&)>> Callbacks;

class CallbackCollection
{
    /*
    CallbackCollection - Maps arbitrary int keys to callbacks to run.
    */

    private:

        std::map<int, Callbacks> callbacks;  // Maps of events to functions

    public:

        void handle_event(SDL_Event& event); // Sends an event through the handlers
        virtual int extract_key(SDL_Event& event); // Extracts a valid key from the event
        void add_callback(int type, std::function<void(SDL_Event&)> func);  // Ties a callback to an event

};

class InputTemp: public CallbackCollection
{
    /*
    InputTemp - Temporary work in progress input system, may get a better name later...

    This input system operates under a callback approach.
    Components can attach callbacks that will be called once a certain event is encountered.
    Multiple callbacks can be tied to a certain event,
    and multiple keys can be attached to a callback.

    We also support callback ordering, which determines the order the callbacks are called in.
    We also support callback pairs(do we?) that will only trigger once a sequence of keys have been encountered,
    such as a key up and down event (This seems really ill defined, maybe this is unecessary?)

    Each callback will be given a reference to the given event.
    This event data can then be used to further process and deal with the event.

    We utilize some recursion to handle nested events.
    For example, keyboard events have data that can differentiae them from others,
    such as KEY_DOWN and KEY_UP, and the type of key that was pressed.
    We do this by creating callbacks that are apart of larger 
    */

    private:

        std::map<int, Callbacks> callbacks;  // Maps of events to functions
        std::vector<SDL_Event&> events;  // List of references to events that have been fired

    public:

        InputTemp();
        ~InputTemp();

        void get_event();  // Gets events from SDL and handles them
        int extract_key(SDL_Event& event);  // Implement the virtual method

};
