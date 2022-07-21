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
    text_renderer = new TextRenderer(start_x, end_x, start_y, end_y);
}

BaseWindow::~BaseWindow() {}

void BaseWindow::add_text(std::string text)
{
    /*
    Adds text to our TextRenderer

    :PARAM text: Text to add
    */

    text_renderer->add(text);
}

void BaseWindow::clear_all_text()
{
    /*
    Erases all text from our TextRenderer
    */

    text_renderer->clear();
}

void BaseWindow::clear_all_sprites()
{
    /*
    Erases and deconstructs all sprites from our vector of sprites
    */

    for(int i = 0; i < sprites.size(); i++)
    {
        delete sprites.at(0);
    }
}

void BaseWindow::resize_window(int start_x, int end_x, int start_y, int end_y)
{
    /*
    Sets the size of the BaseWindows rendering constraints to the passed values
    
    :PARAM start_x: X Coordinate where the screen will start
    :PARAM end_x: X Coordinate where the
    :PARAM start_y:
    :PARAM end_y: 
    
    */

    this->start_x = start_x;
    this->end_x = end_x;
    this->start_y = start_y;
    this->end_y = end_y;
}

void BaseWindow::display()
{
    

    for(Sprite* sprite : sprites)
    {
        sprite->draw();
    }
}