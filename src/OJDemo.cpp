#include <iostream>

#include "OJDemo.h"
#include "TextureHandler.h"
#include "TilemapWindow.h"
#include "TextWindow.h"
#include "Tilemap.h"
#include "ECS.h"
#include "Components/Components.h"
#include "Scripts/Scripts.h"
#include "Debug.h"

TilemapWindow* tilemap_window;
TextWindow* text_window;
TextWindow* full_window;
Tilemap* tilemap;

OJDemo::OJDemo(const char* title, int x, int y, int width, int height) :
    OJAsciiEngine(title, x, y, width, height) 
{
    input_handler = new InputHandler();

    text_window = new TextWindow(texture_handler, int(width / 2) + 1, width,
        0, height, 300);
    text_window->load_font(fonts["ojae"].c_str());

    tilemap = new Tilemap(15, 15);
    
    Entity* dirt = new Entity("Dirt");
    dirt->add_component<TransformComponent>();
    dirt->add_component<SpriteComponent>('~', "Brown", 1);
    tilemap->fill_tilemap(dirt);

    Entity* grass = new Entity("Grass");
    grass->add_component<TransformComponent>();
    grass->add_component<SpriteComponent>('~', "Green", 2);
    tilemap->fill_tilemap(grass);

    Entity* player = new Entity("Player");
    player->add_component<TransformComponent>();
    player->add_component<SpriteComponent>('P', "Blue", 10);
    player->add_component<ColliderComponent>();
    player->add_script(new PlayerInput(input_handler));
    tilemap->add_entity(player, 3, 3);
    // tilemap->add_copy_entity(*player, 5, 5);

    tilemap_window = new TilemapWindow(texture_handler, tilemap, 0, width, 
        0, height);
    tilemap_window->load_font(fonts["ojae"].c_str());

    full_window = new TextWindow(texture_handler, 0, width, 0, height, -1);
    full_window->load_font(fonts["ojae"].c_str());

    Debug::log("[OUT] Demo Initialized");
}

OJDemo::~OJDemo() {}

void OJDemo::start()
{
    startup_screen();
    start_OJAE();
}

void OJDemo::startup_screen()
{   
    full_window->add("OJAE (Owen-Joel ASCII ENGINE)", "White");
    full_window->add("Version: ", "White", false);
    full_window->add("0.2 (Beta)", "White");
    full_window->add("Press Escape to Continue...", "White");

    // Loop until the user presses Escape

    while(true)
    {

        frame_start = SDL_GetTicks64();

        SDL_RenderClear(renderer);
        full_window->display();
        SDL_RenderPresent(renderer);

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                SDL_Quit();
                exit(0);
            }

            else if(event.type == SDL_KEYDOWN &&
                event.key.keysym.sym  == SDLK_ESCAPE)
            {
                return;
            }
        }

        frame_time = SDL_GetTicks64() - frame_start;

        if(FRAME_DELAY > frame_time)
        {
            SDL_Delay(FRAME_DELAY - frame_time);
        }
    }
}

void OJDemo::update() 
{
    text_window->update();
    tilemap_window->update();
    input_handler->update();
}

void OJDemo::handle_events()
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

                default:

                    input_handler->add_key(event.key.keysym.sym);
                    break;
            }
        }

        else if(event.type == SDL_KEYUP)
        {
            input_handler->remove_key(event.key.keysym.sym);
        }
    }
}

void OJDemo::draw() 
{
    clear_screen();
    
    tilemap_window->display();
    text_window->display();

    render();
}
