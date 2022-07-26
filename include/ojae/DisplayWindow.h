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
        InputHandler* input_handler, bool taking_input);
    ~DisplayWindow();

    int get_font();

    void update() override;
    void display() override;
    void draw_text();
    void add_component(Component* component, int x, int y);
    void add_text(std::string text, int x, int y);
    void clear_all_text();
    void clear_all_components();
};