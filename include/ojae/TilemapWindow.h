#pragma once

#include "BaseWindow.h"
#include "Tilemap.h"
#include "InputHandler.h"
#include "TextRenderer.h"

class TilemapWindow : public BaseWindow
{

private:

    Tilemap* tilemap; // Instance of the tilemap

    InputHandler* input_handler; // Instance of the InputHandler
    TextRenderer* text_renderer; // Instance of the TextRenderer


public:

    TilemapWindow();
    TilemapWindow(Tilemap* tilemap, int start_x, int end_x, int start_y,
    int end_y, InputHandler* input_handler, bool taking_input);
    ~TilemapWindow();

    int get_font();

    void display() override; 
    void set_font(int font_size);
};