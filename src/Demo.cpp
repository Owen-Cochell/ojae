#include <iostream>

#include "Demo.h"
#include "TextRenderer.h"
#include "Component.h"
#include "ScrollWindow.h"
#include "TilemapWindow.h"

SDL_Window* Demo::window = nullptr;
SDL_Renderer* Demo::renderer = nullptr;
SDL_Event Demo::event;

bool Demo::running = false;

InputHandler* Demo::input_handler = nullptr;
TextRenderer* text_renderer = nullptr;

TilemapWindow* tilemap_window;

Tilemap* tilemap;

Entity* player;

Demo::Demo() 
{
    screen_width = 0;
    screen_height = 0;
    frame_start = 0;
    frame_time = 0;
    standard_input_delay = 200;
} 

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

    //TilemapWindow
    tilemap = new Tilemap(15, 15);
    tilemap->fill_tilemap(new Tile("Floor", '.', true, 0));
    tilemap->add(new Tile("Chest", 'c', false, 5), 10, 10);

    tilemap_window = new TilemapWindow(tilemap, 0, width / 2, 0, height,
         input_handler, true);

    player = new Entity("Player", 'P', 20);
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
        frame_start = SDL_GetTicks64();

        update();
        handle_events();
        handle_keys();
        draw_all();

        frame_time = SDL_GetTicks64() - frame_start;

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

                    input_handler->add_key(100);
                    break;

                case SDLK_a:

                    input_handler->add_key(97);
                    break;

                case SDLK_w:

                    input_handler->add_key(119);
                    break;

                case SDLK_s:

                    input_handler->add_key(115);
                    break;

                case SDLK_EQUALS:
                    input_handler->add_key(61);
                    break;
                
                case SDLK_MINUS:
                    input_handler->add_key(45);
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

                    input_handler->remove_key(100);
                    break;

                case SDLK_a:

                    input_handler->remove_key(97);
                    break;

                case SDLK_w:

                    input_handler->remove_key(119);
                    break;

                case SDLK_s:

                    input_handler->remove_key(115);
                    break;

                case SDLK_EQUALS:
                    input_handler->remove_key(61);
                    break;
                
                case SDLK_MINUS:
                    input_handler->remove_key(45);
                    break;

                default:
                    break;
            }
        }
    }
}

void Demo::handle_keys()
{
    std::vector<int> keys = input_handler->get_active_keys();

    for(int i : keys)
    {
        switch(i)
        {
            // w
            case 119:
            
                tilemap->move(player, 0, -1);   
                input_handler->set_delay(i, standard_input_delay);
                break;

            // s
            case 115:
                
                tilemap->move(player, 0, 1); 
                input_handler->set_delay(i, standard_input_delay);
                break;

            // w
            case 100:

                tilemap->move(player, 1, 0); 
                input_handler->set_delay(i, standard_input_delay);
                break;

            // a
            case 97:

                tilemap->move(player, -1, 0); 
                input_handler->set_delay(i, standard_input_delay);
                break;

            // =
            case 61:
                //main_window->scroll_down();
                input_handler->set_delay(i, 100);
                break;
            
            // -
            case 45:
                //main_window->scroll_up();
                input_handler->set_delay(i, 100);
                break;

            default:
                break;
        }
    }
}

void Demo::draw_all()
{
    SDL_RenderClear(renderer);
    tilemap_window->display();

    SDL_RenderPresent(renderer);
}

void Demo::quit()
{
    SDL_Quit();
}
