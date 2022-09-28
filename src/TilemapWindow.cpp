#include <map>
#include <iostream>

#include "TilemapWindow.h"


TilemapWindow::TilemapWindow() : BaseWindow()
{
    tilemap = nullptr;
    input_handler = nullptr;
}

TilemapWindow::TilemapWindow(TextureHandler* _texture_handler,
    Debugger* _debugger, Tilemap* tilemap, int start_x, int end_x, 
    int start_y, int end_y, InputHandler* input_handler) : 
    BaseWindow(_texture_handler, _debugger, start_x, end_x, start_y, end_y, true)
{
    this->tilemap = tilemap;
    this->input_handler = input_handler;
}

TilemapWindow::~TilemapWindow() {}

void TilemapWindow::display()
{
    draw_border();

    text_renderer->clear();

    int x_pos = start_x;
    int y_pos = start_y;
    int font_width = text_renderer->get_font_width();
    int font_height = text_renderer->get_font_height();

    for(Character* c : tilemap->get_display())
    {
        
        if(c->symbol == '\n')
        {
            y_pos += font_height * 3;
            x_pos = start_x;
            continue;
        }

        text_renderer->add(c->symbol, c->color, x_pos, y_pos);

        x_pos += font_width * 3; // Multiplied by 3 for the multiple of 2 for 
        // text size, plus a multiple of 1.5 to equally space characters out
        // as they are 1.5 times as wide in the height dimension
    }

    text_renderer->draw();
}

void TilemapWindow::update()
{
    tilemap->update();
}
