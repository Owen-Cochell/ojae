#include "DisplayWindow.h"

DisplayWindow::DisplayWindow() : BaseWindow()
{
    text_renderer = nullptr;
    input_handler = nullptr;
}

DisplayWindow::DisplayWindow(int start_x, int end_x, int start_y, int end_y, 
    InputHandler* input_handler, bool taking_input) :
        BaseWindow(start_x, end_x, start_y, end_y, taking_input)
{
    this->input_handler = input_handler;
    this->text_renderer = new TextRenderer(start_x, end_x, start_y, end_y);
}

DisplayWindow::~DisplayWindow() {}

int DisplayWindow::get_font() { return text_renderer->get_font(); }

void DisplayWindow::update()
{
    /*
    Updates all components
    */

    for(Component* component : components)
    {
        component->update();
    }
}

void DisplayWindow::display()
{
    /*
    Draws all components and text to the screen
    */

    for(Component* component : components)
    {
        component->draw();
    }

    draw_text();
}

void DisplayWindow::draw_text()
{
    /*
    Draws all text to the screen
    */

    text_renderer->draw_all();

}

void DisplayWindow::add_component(Component* component)
{
    /*
    Adds a component to the list of the DisplayWindows components
    */

    components.push_back(component);
}

void DisplayWindow::add_text(std::string text_to_add, int x, int y)
{
    /*
    Adds text to our TextRenderer at the specified coordinates

    :PARAM text: Text to add
    :PARAM x: X coordinate to place the text
    :PARAM y: Y coordinate to place the text
    */

    text_renderer->add(text_to_add, x, y);
}

void DisplayWindow::clear_all_text()
{
    /*
    Erases all text from our text renderer
    */

    text_renderer->clear();
}

void DisplayWindow::clear_all_components()
{
    /*
    Erases and deconstructs all components from our vector of componens
    */

    for(int i = 0; i < components.size(); i++)
    {
        delete components.at(0);
    }
}


