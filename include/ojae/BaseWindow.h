#pragma once

#include <string>
#include <vector>
#include <map>

#include "TextRenderer.h"
#include "InputHandler.h"
#include "Component.h"

class BaseWindow
{
    /*
    Controls the output of text and textures to a set size of the screen. 
    This window cannot be split into multiple parts. For functionality for 
    multiple windows, see Masterwindow and Slavewindows
    */

private:

    int start_x; // X Coordinate where the window begins
    int end_x; // X Coordinate where the window begins
    int start_y; // Y Coordinate where the window begins
    int end_y; // Y Coordinate where the window begins 

    bool taking_input; // Whether this info should handle keys from the input handler

    std::vector<Component*> components; // List of components the window contains
 
    InputHandler* input_handler; // Instance of our InputHandler
    TextRenderer* text_renderer; // Instance of our TextRenderer

public:

    BaseWindow();
    BaseWindow(int start_x, int end_x, int start_y, int end_y, InputHandler* input_handler);
    ~BaseWindow();

    void update();
    void display();
    void draw_text();
    void add_component(Component* component);
    void add_text(std::string text, int x, int y);
    void clear_all_text();
    void clear_all_components();
    void resize_window(int start_x, int end_x, int start_y, int end_y);
};