#pragma once

#include <vector>
#include <functional>
#include <map>

#include <SDL2/SDL.h>


/**
 * @brief 
 * 
 */
struct Key
{
    int id; // The int this key represents
    
    /**
     * @brief Number of frames this key has been pressed without being released
     */
    int frames_active;

    /**
     * @brief // Number of frames this key will be not be allowed to be used
     * until
     */
    int frames_delay; 

    Key() 
    {
        id = 0;
        frames_active = 0;
        frames_delay = 0;
    }
    
    Key(int _id) 
    {
        id = _id;
        frames_active = 0;
        frames_delay = 0;
    }
    
    ~Key() {}

};

class InputHandler
{

private:

    // std::vector<int> keys; // Keys that are currently active

    // /**
    //  * @brief Frame delay before the keys will 
    //  * be allowed to be used again */
    // std::map<int, Uint64> keys_delay; 

    /**
     * @brief Key values that are pressed to their respective key objects
     */
    std::map<int, Key*> keys;


public:

    InputHandler();
    ~InputHandler();

    void update();
    void set_delay(int i, int frames = 10);

    /**
     * @brief Adds a key to the key map if it is not already present
     * 
     * @param key Key to add
     */
    void add_key(int key);
    void remove_key(int key);

    std::vector<Key*> get_active_keys();

};

typedef std::vector<std::function<void(SDL_Event&)>> Callbacks;

class CallbackCollection
{
    /*
    CallbackCollection - Maps arbitrary int keys to callbacks to run.

    This class allows you to map an event to an arbitrary amount of callbacks, and vice versa.
    You can utilize these callbacks to create 'reactive' code,
    which is only ran when an event is encountered.

    We keep a map of keys to values.
    These keys can be any int, and should be extracted from the event by utilizing the 'extract_key()' method.
    From there, we run each function that is tied to the key, along with the GLOBAL callbacks,
    which are called on every event encountered.
    If a key is not found, then we run all callbacks under the UNKOWN key.
    TODO: Implement meta keys, global and unknown

    Each callback will be given a reference to an event 
    */

    protected:

        std::map<int, Callbacks> callbacks;  // Maps of events to functions

    public:

        void handle_event(SDL_Event& event); // Sends an event through the handlers
        virtual int extract_key(SDL_Event& event) {return event.type;}; // Extracts a valid key from the event
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

    Each callback will be given a reference to the given event.
    This event data can then be used to further process and deal with the event.

    We utilize some recursion to handle nested events.
    For example, keyboard events have data that can differentiae them from others,
    such as KEY_DOWN and KEY_UP, and the type of key that was pressed.
    
    Users can also access the keys currently pressed down by accessing the keysarray parameter,
    or by using the access methods.
    */

    private:

        std::vector<SDL_Event> events;  // List of references to events that have been fired

    public:

        InputTemp();
        ~InputTemp();

        const Uint8* keysarray = const_cast <Uint8*> (SDL_GetKeyboardState(NULL));  // Array of keys pressed down

        void get_event();  // Gets events from SDL and handles them
};

class KeyCallbacks: public CallbackCollection
{
    /*
    KeyCallback - Ties callbacks to certain keys.

    We are designed to work with KeyboardEvents.
    Otherwise, we may run into issues.

    The key we extract from the event is 'event.key.keysym.sym',
    which should be an int that represents a certain key.
    */

   public:

        KeyCallbacks();
        ~KeyCallbacks();

        int extract_key(SDL_Event& event) override;
};
