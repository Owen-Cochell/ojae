#pragma once

#include <SDL2/SDL.h>
#include <iostream>

#include "OJAsciiEngine.h"
#include "InputHandler.h"

class OJDemo : public ojae::OJAsciiEngine
{

private:

    InputHandler* input_handler; // Instance of the InputHandler

    Uint64 frame_start; 
    int update_time;
    int handle_time;
    int draw_time;

public:

    OJDemo(const char* title, int x, int y, int width, int height);
    ~OJDemo() override;

    void start();
    void startup_screen();
    void update() override;
    void handle_events() override;
    void draw() override;
};
