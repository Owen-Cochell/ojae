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
#include "CommonDefs.h"
#include "TextFunnel.h"

TilemapWindow* tilemap_window;
TextWindow* frame_window;
TextWindow* text_window;
TextWindow* full_window;
Tilemap* tilemap;
TextFunnel* text_funnel;

OJDemo::OJDemo(const char* title, int x, int y, int width, int height) :
    ojae::OJAsciiEngine(title, x, y, width, height) 
{
    input_handler = new InputHandler();
    text_funnel = new TextFunnel();

    text_window = new TextWindow(texture_handler, int(width / 2) + 1, width,
        (height / 4) + 1, height, 180);
    text_window->load_font(fonts["ojae"].c_str());

    frame_window = new TextWindow(texture_handler, int(width / 2) + 1, width,
        0, (height / 4), -1);
    frame_window->load_font(fonts["ojae"].c_str());

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

    Entity* goblin = new Entity("Goblin");
    goblin->add_component<TransformComponent>();
    goblin->add_component<SpriteComponent>('g', "LGreen", 9);
    goblin->add_component<ColliderComponent>();
    goblin->add_component<DialogueComponent>(text_funnel);
    goblin->add_component<AIMovementComponent>(20);
    goblin->add_script(new TrackEntity(player));
    // goblin->add_script(new DeclareMove());
    tilemap->add_entity(goblin, 5, 5);

    Entity* troll = new Entity("Troll");
    troll->add_component<TransformComponent>();
    troll->add_component<SpriteComponent>('T', "LGreen", 9);
    troll->add_component<ColliderComponent>();
    troll->add_component<AIMovementComponent>(60);
    troll->add_component<DialogueComponent>(text_funnel);
    troll->add_script(new TrackEntity(player));
    // troll->add_script(new DeclareMove());
    tilemap->add_entity(troll, 6, 6);

    Entity* oak_log = new Entity("Oak Tree");
    oak_log->add_component<TransformComponent>();
    oak_log->add_component<SpriteComponent>('T', "Tan", 5);
    oak_log->add_component<ColliderComponent>();
    oak_log->set_entity_handler(tilemap->get_entity_handler());

    Entity* stone = new Entity("Stone");
    stone->add_component<TransformComponent>();
    stone->add_component<SpriteComponent>('S', "LGray", 5);
    stone->add_component<ColliderComponent>();
    tilemap->add_entity(stone, 0, 0);

    for(int x = 1; x < tilemap->get_width(); x++)
    {
        tilemap->add_copy_entity(*stone, x, 0);
        tilemap->add_copy_entity(*stone, x, tilemap->get_height() - 1);
    }

    for(int y = 1; y < tilemap->get_height(); y++)
    {
        tilemap->add_copy_entity(*stone, 0, y);
        tilemap->add_copy_entity(*stone, tilemap->get_width() - 1, y);
    }

    std::vector<std::pair<int,int>> available_pos;

    for(int y = 0; y < tilemap->get_height(); y++)
    {
        for(int x = 0; x < tilemap->get_width(); x++)
        {
            if(CollisionHandler::is_traversable(oak_log, x, y))
            {

                available_pos.push_back({x, y});
            }
        }
    }

    if(available_pos.size() > 0)
    {
        int index = Random::get_random_num(0, available_pos.size() - 1);
        tilemap->add_entity(oak_log, available_pos.at(index).first, available_pos.at(index).second);
        available_pos.erase(available_pos.begin() + index);

        for(int i = 0; i < tilemap->get_width(); i++)
        {
            index = Random::get_random_num(0, available_pos.size() - 1);
            tilemap->add_copy_entity(*oak_log, available_pos.at(index).first, available_pos.at(index).second);
            available_pos.erase(available_pos.begin() + index);
        }
    }

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
    frame_start = SDL_GetTicks64();

    text_window->update();
    frame_window->update();
    tilemap_window->update();
    input_handler->update();

    frame_window->clear();
    frame_window->add("Update: ", "White", false);
    frame_window->add(std::to_string(update_time), "White");
    frame_window->add("Handle Events: ", "White", false);
    frame_window->add(std::to_string(handle_time), "White");
    frame_window->add("Draw: ", "White", false);
    frame_window->add(std::to_string(draw_time), "White");

    for(std::pair<std::string,std::string> element : 
        text_funnel->get_contents())
    {
        text_window->add(element.first, element.second);
    }
    text_funnel->clear();

    update_time = SDL_GetTicks64() - frame_start;
}

void OJDemo::handle_events()
{
    frame_start = SDL_GetTicks64();

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

    handle_time = SDL_GetTicks64() - frame_start;
}

void OJDemo::draw() 
{
    frame_start = SDL_GetTicks64();

    clear_screen();
    
    tilemap_window->display();
    frame_window->display();
    text_window->display();
    render();

    draw_time = SDL_GetTicks64() - frame_start;
}
