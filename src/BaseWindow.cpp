#include "BaseWindow.h"
#include "TextureHandler.h"

BaseWindow::BaseWindow()
{
    resize_window(0, 0, 0, 0);
    taking_input = false;
    border = TextureHandler::load_texture("assets/Border.png");
}

BaseWindow::BaseWindow(int start_x, int end_x, int start_y, int end_y, bool taking_input)
{
    resize_window(start_x, end_x, start_y, end_y);
    this->taking_input = taking_input;
    border = TextureHandler::load_texture("assets/Border.png");
}

BaseWindow::~BaseWindow() {}

void BaseWindow::update() {}

void BaseWindow::display() {}

void BaseWindow::draw_border()
{
    //Draw Borders
    TextureHandler::draw(border, border_src, top_border);
    TextureHandler::draw(border, border_src, right_border);
    TextureHandler::draw(border, border_src, bottom_border);
    TextureHandler::draw(border, border_src, left_border);
}

void BaseWindow::resize_window(int start_x, int end_x, int start_y, int end_y)
{
    /*
    Sets the size of the DisplayWindows rendering constraints to the passed 
    values and configures the Rects for the borders to accurately wrap around 
    the new size.
    
    :PARAM start_x: X Coordinate where the screen will start
    :PARAM end_x: X Coordinate where the screen ends
    :PARAM start_y: Y Coordinate where the screen starts
    :PARAM end_y: Y Coordinate where the screen ends
    */

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
