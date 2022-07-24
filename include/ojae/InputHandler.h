#pragma once

#include <vector>
#include <map>

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