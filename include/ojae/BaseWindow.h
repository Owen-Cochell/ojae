#include <string>
#include <vector>

#include "TextRenderer.h"
#include "InputHandler.h"
#include "Sprite.h"

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

    int cursor_index; // Start index of where we start renderering text

    bool taking_input; // Whether this info should handle keys from the input handler

    std::vector<Sprite*> sprites; // List of sprites the window contains

    TextRenderer* text_renderer; // Instance of our TextRenderer
    InputHandler* input_handler; // Instance of our InputHandler
    

public:

    BaseWindow();
    BaseWindow(int start_x, int end_x, int start_y, int end_y, InputHandler* input_handler);
    ~BaseWindow();

    void add_text(std::string text);
    void clear_all_text();
    void clear_all_sprites();
    void resize_window(int start_x, int end_x, int start_y, int end_y);
    void display();
};