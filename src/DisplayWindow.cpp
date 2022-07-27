#include <iostream>

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
    this->text_renderer = new TextRenderer(this->start_x, this->end_x, 
        this->start_y, this->end_y);
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

    draw_border();

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

void DisplayWindow::add_component(Component* component, int x, int y)
{
    /*
    Adds a component to the list of the DisplayWindows components

    :PARAM component: Component to add
    :PARAM x: X coordinate to place the component in relation to the windows starting position
    :PARAM y: Y coordinate to place the component in relation to the windows starting position
    */

    components.push_back(component);
    component->set_position(start_x + x, start_y + y);
}

void DisplayWindow::add_text(std::string text_to_add, int x, int y)
{
    /*
    Adds text to our TextRenderer at the specified coordinates

    :PARAM text: Text to add
    :PARAM x: X coordinate to place the text in relation to the windows starting position
    :PARAM y: Y coordinate to place the text in relation to the windows starting position
    */

    text_renderer->add(text_to_add, x, y);
}

void DisplayWindow::move(Component* component, int x, int y)
{
    /*
    Moves a component to a spot within the DisplayWindow. If the target spot
    is outside window dimensions, the component will be moved as close to the 
    border as possible

    :PARAM component: Component to move
    :PARAM x: X Coordinate
    :PARAM y: Y Coordinate
    */

    if(x < start_x)
    {
        x = start_x;
    }

    else if(x > end_x - component->get_width())
    {
        x = end_x - component->get_width();
    }

    if(y < start_y)
    {
        y = start_y;
    }

    else if(y > end_y - component->get_height())
    {
        y = end_y - component->get_height();
    }

    component->set_position(x, y);

    // if(
    //     x > start_x && 
    //     x < end_x - component->get_width() && 
    //     y > start_y &&
    //     y < end_y - component->get_height()
    // )
    // {
    //     component->set_position(x, y);
    // }
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


