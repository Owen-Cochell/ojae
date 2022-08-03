#include <iostream>

#include "DisplayWindow.h"

DisplayWindow::DisplayWindow() : BaseWindow()
{
    text_renderer = nullptr;
    input_handler = nullptr;
}

DisplayWindow::DisplayWindow(int start_x, int end_x, int start_y, int end_y, 
    InputHandler* input_handler, bool taking_input, int text_limit) :
        BaseWindow(start_x, end_x, start_y, end_y, taking_input)
{
    this->input_handler = input_handler;
    this->text_renderer = new TextRenderer(this->start_x, this->end_x, 
        this->start_y, this->end_y, text_limit);
}

DisplayWindow::~DisplayWindow() {}

int DisplayWindow::get_font() { return text_renderer->get_font(); }

void DisplayWindow::update()
{
    /*
    Updates all components and our text renderer
    */

    for(Component* component : components)
    {
        component->update();
    }

    text_renderer->update();
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

void DisplayWindow::scroll_up()
{
    if(text_renderer->display_start - (get_font() * 1.5) >= 0)
    {
        text_renderer->display_start -= (get_font() * 1.5);
    }
}

void DisplayWindow::scroll_down()
{
    if(text_renderer->display_start + (end_y - start_y)
     + (get_font() * 1.5) < text_renderer->get_largest_y())
    {
        text_renderer->display_start += (get_font() * 1.5);
    }
}

void DisplayWindow::draw_text()
{
    /*
    Draws all text to the screen
    */

    text_renderer->draw_all();

}

void DisplayWindow::set_cursor_pos(int x, int y)
{
    text_renderer->set_cursor_pos(x, y);
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

void DisplayWindow::add_text(std::string text)
{
    /*
    Adds text to our TextRenderer at the specified coordinates

    :PARAM text: Text to add
    :PARAM x: X coordinate to place the text in relation to the windows starting position
    :PARAM y: Y coordinate to place the text in relation to the windows starting position
    */

    text_renderer->add(text);
}

void DisplayWindow::add_text(char text)
{
    text_renderer->add(text);
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
    Erases all text from the text renderer
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


