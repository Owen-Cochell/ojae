#pragma once

#include "BaseWindow.h"
#include "InputHandler.h"
#include "TextRenderer.h"
#include "TextureHandler.h"
#include "Debugger.h"
#include "Text.h"

class TextWindow : public BaseWindow
{
    
private:

    /**
     * @brief Contents to render each frame. Contains Character structs that 
     * hold data for rendering and deletion
     */
    std::vector<Text*> contents;
    
    InputHandler* input_handler; // Instance of the InputHandler

    /**
     * @brief  Amount of time each member of the contents will stay in 
        // in the contents, until it is removed automatically
     * 
     */
    int life_time;

public:

    TextWindow();
    TextWindow(TextureHandler* _texture_handler, 
        int start_x, int end_x, int start_y, int end_y, 
        int life_time);
    ~TextWindow();

    void update() override;
    void display() override;
    void add(std::string new_content, std::string color, bool new_line = true);
    void clear();
    // void set_font(int font_size);
};



