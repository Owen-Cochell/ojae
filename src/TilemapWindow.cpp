#include <map>
#include <iostream>

#include "TilemapWindow.h"


TilemapWindow::TilemapWindow() : BaseWindow()
{
    tilemap = nullptr;
    input_handler = nullptr;
    text_renderer = nullptr;
}

TilemapWindow::TilemapWindow(Tilemap* tilemap, int start_x, int end_x,
    int start_y, int end_y, InputHandler* input_handler) : 
    BaseWindow(start_x, end_x, start_y, end_y, true)
{
    this->tilemap = tilemap;
    this->input_handler = input_handler;
    text_renderer = new TextRenderer(this->start_x, this->end_x, 
        this->start_y, this->end_y);
}

TilemapWindow::~TilemapWindow()
{
    delete text_renderer;
}

int TilemapWindow::get_font() { return text_renderer->get_font(); }

void TilemapWindow::display()
{
    /*
    Called once per frame. Renders the tilemap to the window
    */

    draw_border();
    text_renderer->clear();

    int x_pos = start_x + border_size;
    int y_pos = start_y + border_size;
    int font = text_renderer->get_font();

    for(char c : tilemap->get_display())
    {
        
        if(c == '\n')
        {
            y_pos += font * 2;
            x_pos = start_x + border_size;
            continue;
        }

        text_renderer->add(c, x_pos, y_pos);

        x_pos += font * 2;
    }

    text_renderer->draw();
}

void TilemapWindow::set_font(int font_size)
{
    text_renderer->set_font(font_size);
}