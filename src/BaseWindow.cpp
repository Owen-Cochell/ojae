#include "BaseWindow.h"

BaseWindow::BaseWindow() 
{
    resize_window(0, 0, 0, 0);
    text_renderer = nullptr;
    input_handler = nullptr;
}

BaseWindow::BaseWindow(int start_x, int end_x, int start_y, int end_y, 
    InputHandler* input_handler)
{
    resize_window(start_x, end_x, start_y, end_y);
    this->input_handler = input_handler;
    this->text_renderer = new TextRenderer(start_x, end_x, start_y, end_y);
}

BaseWindow::~BaseWindow() {}

void BaseWindow::update()
{
    /*
    Updates all components
    */

    for(Component* component : components)
    {
        component->update();
    }
}

void BaseWindow::display()
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

void BaseWindow::draw_text()
{
    /*
    Draws all text to the screen
    */

    text_renderer->draw_all();

}

void BaseWindow::add_component(Component* component)
{
    /*
    Adds a component to the list of the BaseWindows components
    */

    components.push_back(component);
}

void BaseWindow::add_text(std::string text_to_add, int x, int y)
{
    /*
    Adds text to our TextRenderer at the specified coordinates

    :PARAM text: Text to add
    :PARAM x: X coordinate to place the text
    :PARAM y: Y coordinate to place the text
    */

    text_renderer->add(text_to_add, x, y);
}

void BaseWindow::clear_all_text()
{
    /*
    Erases all text from our text renderer
    */

    text_renderer->clear();
}

void BaseWindow::clear_all_components()
{
    /*
    Erases and deconstructs all components from our vector of componens
    */

    for(int i = 0; i < components.size(); i++)
    {
        delete components.at(0);
    }
}

void BaseWindow::resize_window(int start_x, int end_x, int start_y, int end_y)
{
    /*
    Sets the size of the BaseWindows rendering constraints to the passed values
    
    :PARAM start_x: X Coordinate where the screen will start
    :PARAM end_x: X Coordinate where the screen ends
    :PARAM start_y: Y Coordinate where the screen starts
    :PARAM end_y: Y Coordinate where the screen ends
    */

    this->start_x = start_x;
    this->end_x = end_x;
    this->start_y = start_y;
    this->end_y = end_y;
}

