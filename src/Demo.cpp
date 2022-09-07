#include <iostream>
#include <fstream>

#include "Demo.h"
#include "Player.h"
#include "TextRenderer.h"
#include "TextureHandler.h"
#include "TextWindow.h"
#include "TilemapWindow.h"
#include "TextFunnel.h"

static std::fstream file_stream;

SDL_Window* Demo::window = nullptr;
SDL_Renderer* Demo::renderer = nullptr;
SDL_Event Demo::event;

bool Demo::running = false;

InputHandler* Demo::input_handler = nullptr;
TextFunnel* text_funnel = nullptr;

TilemapWindow* tilemap_window;
TextWindow* text_window;

Tilemap* tilemap;

Player* player;

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

    debugger = new Debugger("OutputLog.txt");

    debugger->log("[OUT] Initializing SDL");

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
        SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
    }

    debugger->log("[OUT] Creating Handler Objects");

    texture_handler = new TextureHandler(renderer, debugger);

    input_handler = new InputHandler();
    text_funnel = new TextFunnel();

    // TextWindow
    text_window = new TextWindow(texture_handler, debugger,
        int(width / 2) + 1, width, 0, height, input_handler, 5000);

    text_window->add("Content");

    player = new Player(input_handler, text_funnel, "Player", 'P');

    tilemap = new Tilemap(text_funnel, player, 10, 10);
    tilemap->fill_tilemap(new Tile("Floor", '.', true, 0));
    tilemap->add(new Tile("Chest", 'C', false, 5), 8, 8);

    // TilemapWindow
    tilemap_window = new TilemapWindow(texture_handler, debugger, tilemap,
        0, width / 2, 0, height, input_handler);

    tilemap->add(player, 3, 3);

    debugger->log("[OUT] Done");
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
        //handle_keys();
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
    text_window->update();
    input_handler->update();

    tilemap->update_all_entities();
    tilemap->move_all_entities();

    tilemap->update_player();
    tilemap->move_player();

    for(std::string element : text_funnel->get_contents())
    {
        text_window->add(element);
    }

    text_funnel->clear();
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

/*
void Demo::handle_keys()
{
    std::vector<int> keys = input_handler->get_active_keys();

    for(int i : keys)
    {

        switch(i)
        {
            // w
            case 119:

                tilemap->move(player);
                input_handler->set_delay(i, standard_input_delay);
                break;

            // s
            case 115:
                
                tilemap->move(player); 
                input_handler->set_delay(i, standard_input_delay);
                break;

            // w
            case 100:

                tilemap->move(player); 
                input_handler->set_delay(i, standard_input_delay);
                break;

            // a
            case 97:

                tilemap->move(player); 
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
*/

void Demo::draw_all()
{
    SDL_RenderClear(renderer);
   
    tilemap_window->display();
    text_window->display();

    SDL_RenderPresent(renderer);
}

void Demo::quit()
{
    SDL_Quit();
}
