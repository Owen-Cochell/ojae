#pragma once

#include "BaseWindow.h"
#include "InputHandler.h"
#include "TextRenderer.h"
#include "Component.h"

class DisplayWindow : public BaseWindow
{

private:

    std::vector<Component*> components; // List of components the window contains
 
    InputHandler* input_handler; // Instance of the InputHandler
    TextRenderer* text_renderer; // Instance of the TextRenderer

public:

    DisplayWindow();
    DisplayWindow(int start_x, int end_x, int start_y, int end_y, 
        InputHandler* input_handler, bool taking_input, int text_limit);
    ~DisplayWindow();

    int get_font();

    void update() override;
    void display() override;
    void scroll_up();
    void scroll_down();
    void draw_text();
    void set_cursor_pos(int x, int y);
    void add_component(Component* component, int x, int y);
    void add_text(std::string text);
    void add_text(char text);
    void move(Component* component, int x, int y);
    void clear_all_text();
    void clear_all_components();
};