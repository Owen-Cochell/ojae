#include <iostream>

#include "BaseWindow.h"
#include "TextureHandler.h"

BaseWindow::BaseWindow()
{
    resize_window(0, 0, 0, 0);
    taking_input = false;
    texture_handler = nullptr;
    text_renderer = nullptr;
    debugger = nullptr;
    border = texture_handler->load_texture("assets/border.png");
    border_selected = texture_handler->load_texture("assets/border_selected.png");
}

BaseWindow::BaseWindow(TextureHandler* _texture_handler, Debugger* _debugger, 
    int start_x, int end_x, int start_y, int end_y, bool taking_input)
{

    resize_window(start_x, end_x, start_y, end_y);
    this->taking_input = taking_input;
    texture_handler = _texture_handler;
    debugger = _debugger;

    border = texture_handler->load_texture("assets/border.png");
    border_selected = texture_handler->load_texture("assets/border_selected.png");
    text_renderer = new TextRenderer(_texture_handler, _debugger,
        this->start_x, this->end_x, this->start_y, this->end_y);
}

BaseWindow::~BaseWindow() 
{
    delete text_renderer;
}

std::string BaseWindow::get_font_path() 
{ 
    return text_renderer->get_font_path(); 
}   

void BaseWindow::load_font(const char* path)
{
    text_renderer->load_font(path);
}

void BaseWindow::update() {}

void BaseWindow::display() {}

void BaseWindow::draw_border()
{

    SDL_Texture* targ_texture = border;

    if(taking_input)
    {
        targ_texture = border_selected;
    }
    
    //Draw Borders
    texture_handler->draw(targ_texture, border_src, top_border);
    texture_handler->draw(targ_texture, border_src, right_border);
    texture_handler->draw(targ_texture, border_src, bottom_border);
    texture_handler->draw(targ_texture, border_src, left_border);
}

/**
 * @brief Sets the size of the BaseWindow's rendering constraints to the 
 *  passed values, and configures the Rects for the borders to accurately wrap
 *  around the new size.
 * 
 * @param start_x X Coordinate where the screen will start
 * @param end_x X Coordinate where the screen ends
 * @param start_y Y Coordinate where the screen starts
 * @param end_y Y Coordinate where the screen ends
 */
void BaseWindow::resize_window(int start_x, int end_x, int start_y, int end_y)
{
    border_size = 8;

    // Reset window dimensions with respect for border room
    this->start_x = start_x + border_size + 1;
    this->end_x = end_x - border_size - 1;
    this->start_y = start_y + border_size + 1;
    this->end_y = end_y - border_size - 1;

    // Establish Border Image Source dimensions
    border_src.x = 0;
    border_src.y = 0;
    border_src.w = 1;
    border_src.h = 1;

    // Establish Top Border dimensions
    top_border.x = start_x;
    top_border.y = start_y;
    top_border.w = end_x - start_x;
    top_border.h = border_size;

    // Establish Right Border dimensions
    right_border.x = end_x - border_size;
    right_border.y = start_y;
    right_border.w = border_size;
    right_border.h = end_y;

    // Establish Bottom Border dimensions
    bottom_border.x = start_x;
    bottom_border.y = end_y - border_size;
    bottom_border.w = end_x - start_x;
    bottom_border.h = border_size;

    // Establish Left Border Dimensions
    left_border.x = start_x;
    left_border.y = start_y;
    left_border.w = border_size;
    left_border.h = end_y;
}
