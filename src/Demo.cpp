#include "Demo.h"
#include "TextRenderer.h"
#include "Component.h"
#include "BaseWindow.h"

SDL_Window* Demo::window = nullptr;
SDL_Renderer* Demo::renderer = nullptr;
SDL_Event Demo::event;

bool Demo::running = false;

InputHandler* Demo::input_handler = nullptr;
TextRenderer* text_renderer = nullptr;

Component* red_box;

BaseWindow* main_window;

Demo::Demo() {}

Demo::~Demo() {}

void Demo::init(const char* title, int x, int y, int width, int height,
    bool fullscreen)
{

    screen_width = width;
    screen_height = height;

    int flags = 0;

    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = SDL_CreateWindow(title, x, y, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 27, 27, 65, 255);
    }

    input_handler = new InputHandler();

    main_window = new BaseWindow(0, width, 0, height, input_handler);

    red_box = new Component("Red Box", "assets/red_box.png", 0, 0, 16, 16, 
        200, 200, 16, 16);

    main_window->add_component(red_box);
    main_window->add_text("Text", 0, 100);
}

void Demo::start()
{
    running = true;
    execution_loop();
}

void Demo::execution_loop()
{
    /*
    Runs our main simulation, at 60 frames per second
    */

    while(running)
    {
        frame_start = SDL_GetTicks();

        update();
        handle_events();
        handle_keys();
        draw_all();

        frame_time = SDL_GetTicks() - frame_start;

        if(FRAME_DELAY > frame_time)
        {
            SDL_Delay(FRAME_DELAY - frame_time);
        }
    }

    quit();
}

void Demo::update()
{
    input_handler->update();
    main_window->update();
}

void Demo::handle_events()
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            running = false;
        }

        else if(event.type == SDL_KEYDOWN)
        {

            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    running = false;
                    break;

                case SDLK_d:

                    input_handler->add_key('d');
                    break;

                case SDLK_a:

                    input_handler->add_key('a');
                    break;

                case SDLK_w:

                    input_handler->add_key('w');
                    break;

                case SDLK_s:

                    input_handler->add_key('s');
                    break;

                default:
                    break;
            }
        }

        else if(event.type == SDL_KEYUP)
        {

            switch(event.key.keysym.sym)
            {

                case SDLK_d:

                    input_handler->remove_key('d');
                    break;

                case SDLK_a:

                    input_handler->remove_key('a');
                    break;

                case SDLK_w:

                    input_handler->remove_key('w');
                    break;

                case SDLK_s:

                    input_handler->remove_key('s');
                    break;

                default:
                    break;
            }
        }
    }
}

void Demo::handle_keys()
{
    std::vector<char> keys = input_handler->get_active_keys();

    for(char c : keys)
    {
        switch(c)
        {
            case 'w':
                red_box->increment_y(-10);
                break;

            case 's':
                red_box->increment_y(10);
                break;

            case 'd':
                red_box->increment_x(10);
                break;

            case 'a':
                red_box->increment_x(-10);
                break;

            default:
                break;
        }
   
        input_handler->set_delay(c, 20);
    }
}

void Demo::draw_all()
{
    SDL_RenderClear(renderer);

    main_window->display();

    SDL_RenderPresent(renderer);
}

void Demo::quit()
{
    SDL_Quit();
}
