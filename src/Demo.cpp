#include <iostream>

#include "Demo.h"
#include "TextRenderer.h"
#include "Component.h"
#include "DisplayWindow.h"
#include "TilemapWindow.h"

SDL_Window* Demo::window = nullptr;
SDL_Renderer* Demo::renderer = nullptr;
SDL_Event Demo::event;

bool Demo::running = false;

InputHandler* Demo::input_handler = nullptr;
TextRenderer* text_renderer = nullptr;

Component* red_box;

DisplayWindow* main_window;
TilemapWindow* tilemap_window;

Tile* player;

Demo::Demo() {}

Demo::~Demo() {}

void Demo::init(const char* title, int x, int y, int width, int height,
    bool fullscreen)
{
    screen_width = width;
    screen_height = height;

    _player_speed = 16;
    _player_delay = 0;

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

    //DisplayWindow
    main_window = new DisplayWindow(width / 2, width, 0, height, input_handler, true);

    red_box = new Component("Red Box", "assets/red_box.png", 0, 0, 16, 16, 
        0, 0, 16, 16);

    main_window->add_component(red_box, 0, 64);


    //TilemapWindow
    Tilemap* tilemap = new Tilemap(10, 10);
    tilemap->fill_tilemap(new Tile("Floor", '.'));

    tilemap_window = new TilemapWindow(tilemap, 0, width / 2, 0, height,
        input_handler, true);

    player = new Tile("Player", 'P');
    tilemap->add(player, 3, 3);
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
    main_window->clear_all_text();
    main_window->add_text("Speed: ", 0, 0);
    main_window->add_text(std::to_string(_player_speed), 112, 0);
    main_window->add_text("Delay: ", 0, 20);
    main_window->add_text(std::to_string(_player_delay), 112, 20);

    main_window->update();
    input_handler->update();
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

                case SDLK_EQUALS:
                    input_handler->add_key('=');
                    break;
                
                case SDLK_MINUS:
                    input_handler->add_key('-');
                    break;

                case SDLK_LEFTBRACKET:
                    input_handler->add_key('[');
                    break;
                
                case SDLK_RIGHTBRACKET:
                    input_handler->add_key(']');
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

                case SDLK_EQUALS:
                    input_handler->remove_key('=');
                    break;
                
                case SDLK_MINUS:
                    input_handler->remove_key('-');
                    break;

                case SDLK_LEFTBRACKET:
                    input_handler->remove_key('[');
                    break;
                
                case SDLK_RIGHTBRACKET:
                    input_handler->remove_key(']');
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

                main_window->move(red_box, red_box->get_x(), 
                    red_box->get_y() - _player_speed);
                input_handler->set_delay(c, _player_delay);
                break;

            case 's':
                
                main_window->move(red_box, red_box->get_x(), 
                    red_box->get_y() + _player_speed);
                input_handler->set_delay(c, _player_delay);
                break;

            case 'd':

                main_window->move(red_box, 
                    red_box->get_x() + _player_speed, red_box->get_y());
                input_handler->set_delay(c, _player_delay);
                break;

            case 'a':

                main_window->move(red_box, 
                    red_box->get_x() - _player_speed, red_box->get_y());
                input_handler->set_delay(c, _player_delay);
                break;

            case '=':
                break;
            
            case '-':
                break;

            case ']':
                break;
            
            case '[':
                break;

            default:
                break;
        }
    }
}

void Demo::draw_all()
{
    SDL_RenderClear(renderer);

    main_window->display();
    tilemap_window->display();

    SDL_RenderPresent(renderer);
}

void Demo::quit()
{
    SDL_Quit();
}
