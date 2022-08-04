#pragma once

#include "BaseWindow.h"
#include "InputHandler.h"
#include "TextRenderer.h"

class TextWindow : public BaseWindow
{
    
private:

    std::vector<std::pair<std::string, Uint32>> contents; // Contents to render
        // each frame, containing the contents, and the time stamp of when to 
        // remove this string from the contents
    
    InputHandler* input_handler; // Instance of the InputHandler
    TextRenderer* text_renderer; // Instance of the TextRenderer

    int life_time; // Amount of time each member of the contents will stay in 
        // in the contents, until it is removed automatically

public:

    TextWindow();
    TextWindow(int start_x, int end_x, int start_y, int end_y,
        InputHandler* input_handler, int life_time);
    ~TextWindow();

    void update() override;
    void display() override;
    void add(std::string new_content);
    void clear();
    void set_font(int font_size);
};