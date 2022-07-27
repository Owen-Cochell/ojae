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
    int start_y, int end_y, InputHandler* input_handler, bool taking_input) : 
    BaseWindow(start_x, end_x, start_y, end_y, taking_input)
{
    this->tilemap = tilemap;
    this->input_handler = input_handler;
    text_renderer = new TextRenderer(this->start_x, this->end_x, 
        this->start_y, this->end_y);
}

int TilemapWindow::get_font() { return text_renderer->get_font(); }

void TilemapWindow::display()
{
    /*
    Called once per frame. Renders the tilemap to the window
    */

    draw_border();

    text_renderer->clear();
    tilemap->assemble_tilemap();

    std::map<std::pair<int,int>,char> tilemap_display = tilemap->get_display();

    for(std::map<std::pair<int,int>,char>::iterator it = 
        tilemap_display.begin(); it != tilemap_display.end(); it++)
    {
        text_renderer->add(std::string(1, it->second), 
        it->first.first * text_renderer->get_font(), it->first.second * 
        text_renderer->get_font());
    }

    text_renderer->draw_all();
}

void TilemapWindow::set_font(int font_size)
{
    text_renderer->set_font(font_size);
}