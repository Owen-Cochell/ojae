#pragma once

#include <string>
#include <vector>
#include <map>

class BaseWindow
{
    /*
    Controls the output of text and textures to a set size of the screen. 
    This window cannot be split into multiple parts. For functionality for 
    multiple windows, see Masterwindow and Slavewindows
    */

protected:

    int start_x; // X Coordinate where the window begins
    int end_x; // X Coordinate where the window begins
    int start_y; // Y Coordinate where the window begins
    int end_y; // Y Coordinate where the window begins 

    bool taking_input; // Whether this info should handle keys from the input handler


public:

    BaseWindow();
    BaseWindow(int start_x, int end_x, int start_y, int end_y, bool taking_input);
    ~BaseWindow();

    virtual void update();
    virtual void display();
    void resize_window(int start_x, int end_x, int start_y, int end_y);
};