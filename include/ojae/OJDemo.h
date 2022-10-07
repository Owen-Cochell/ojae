#pragma once

#include "OJAsciiEngine.h"
#include "InputHandler.h"

class OJDemo : public OJAsciiEngine
{

private:

    InputHandler* input_handler; // Instance of the InputHandler

public:

    OJDemo(const char* title, int x, int y, int width, int height);
    ~OJDemo() override;

    void start();
    void startup_screen();
    void update() override;
    void handle_events() override;
    void draw() override;
};
