#pragma once

#include <string>

#include "BaseWindow.h"
#include "InputHandler.h"
#include "TextRenderer.h"
#include "Debugger.h"
#include "Tilemap.h"

class TilemapWindow : public BaseWindow
{

private:

    Tilemap* tilemap; // Instance of the tilemap

    InputHandler* input_handler; // Instance of the InputHandler


public:

    TilemapWindow();
    TilemapWindow(TextureHandler* _texture_handler,
        Tilemap* tilemap, int start_x, int end_x, int start_y, int end_y);
    ~TilemapWindow();

    void display() override;
    void update() override;
};