#pragma once

#include <vector>

class InputHandler
{

private:

    static std::vector<char> keys;

public:

    InputHandler();
    ~InputHandler();

    void set_keys(std::vector<char> new_keys);
    void add_key(char key);
    void remove_key(char key);

    std::vector<char> get_active_keys();

};