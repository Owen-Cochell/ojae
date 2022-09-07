#include <map>

#include "TilemapWindow.h"


TilemapWindow::TilemapWindow() : BaseWindow()
{
    tilemap = nullptr;
    input_handler = nullptr;
    text_renderer = nullptr;
}

TilemapWindow::TilemapWindow(TextureHandler* _texture_handler,
    Debugger* _debugger, Tilemap* tilemap, int start_x, int end_x, 
    int start_y, int end_y, InputHandler* input_handler) : 
    BaseWindow(_texture_handler, _debugger, start_x, end_x, start_y, end_y, true)
{
    this->tilemap = tilemap;
    this->input_handler = input_handler;
    text_renderer = new TextRenderer(_texture_handler, _debugger,
        this->start_x, this->end_x, this->start_y, this->end_y);
}

TilemapWindow::~TilemapWindow()
{
    delete text_renderer;
}

// int TilemapWindow::get_font() { return text_renderer->get_font(); }

/**
 * @brief Called once per frame. Renders the tilemap to the window */

void TilemapWindow::display()
{

    draw_border();
    text_renderer->clear();

    int x_pos = start_x;
    int y_pos = start_y;
    int font_width = text_renderer->get_font_width();
    int font_height = text_renderer->get_font_height();

    // debugger->log("[OUT] X Pos : ", true, false);
    // debugger->log(x_pos, false);
    // debugger->log("[OUT] Y Pos : ", true, false);
    // debugger->log(y_pos, false);
    // debugger->log("[OUT] Font Width: ", true, false);
    // debugger->log(font_width, false);
    // debugger->log("[OUT] Font Height: ", true, false);
    // debugger->log(font_height, false);


    for(char c : tilemap->get_display())
    {
        
        if(c == '\n')
        {
            y_pos += font_height * 3;
            x_pos = start_x;
            continue;
        }

        text_renderer->add(c, x_pos, y_pos);
        // debugger->log("[OUT] Adding character ", true, false);
        // debugger->log(c, false, false);
        // debugger->log(" at position: (", false, false);
        // debugger->log(x_pos, false, false);
        // debugger->log(", ", false, false);
        // debugger->log(y_pos, false, false);
        // debugger->log(")", false);

        x_pos += font_width * 3; // Multiplied by 3 for the multiple of 2 for 
        // text size, plsu a multiple of 1.5 to equally space characters out
        // as they are 1.5 times as wide in the height dimension
    }

    text_renderer->draw();
}

// void TilemapWindow::set_font(int font_size)
// {
//     text_renderer->set_font(font_size);
// }