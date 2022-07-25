#include "BaseWindow.h"

BaseWindow::BaseWindow()
{
    resize_window(0, 0, 0, 0);
    taking_input = false;
}

BaseWindow::BaseWindow(int start_x, int end_x, int start_y, int end_y, bool taking_input)
{
    resize_window(start_x, end_x, start_y, end_y);
    this->taking_input = taking_input;
}

BaseWindow::~BaseWindow() {}

void BaseWindow::update() {}

void BaseWindow::display() {}

void BaseWindow::resize_window(int start_x, int end_x, int start_y, int end_y)
{
    /*
    Sets the size of the DisplayWindows rendering constraints to the passed values
    
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