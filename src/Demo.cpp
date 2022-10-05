#include <fstream>
#include <iostream>

#include "Demo.h"
#include "ECS.h"
#include "TextRenderer.h"
#include "TextureHandler.h"
#include "TextWindow.h"
#include "TilemapWindow.h"
#include "TextFunnel.h"
#include "Tilemap.h"
#include "Components/Components.h"
#include "Scripts/Scripts.h"
#include "Heap.h"
#include "Jloader.h"

static std::fstream file_stream;

SDL_Window* Demo::window = nullptr;
SDL_Renderer* Demo::renderer = nullptr;
SDL_Event Demo::event;

bool Demo::running = false;

InputHandler* Demo::input_handler = nullptr;
TextFunnel* text_funnel = nullptr;

TilemapWindow* tilemap_window;
TextWindow* text_window;
TextWindow* full_window;

SDL_Rect src, dest;

Tilemap* tilemap;

Entity* player;

std::string determine_color(int num, int max)
{
    float ratio = num / max;

    if(ratio <= .3) { return "Green"; }
    else if(ratio > .3 && ratio <= .5) { return "Yellow"; }
    else if(ratio > .5 && ratio <= .8) { return "Orange"; }
    return "Red";
}

// Constructors/Deconstructors

Demo::Demo() 
{
    screen_width = 0;
    screen_height = 0;
    frame_start = 0;
    frame_time = 0;
    standard_input_delay = 200;
    debugger = new Debugger("OutputLog.txt");
    input_handler = new InputHandler();
    text_funnel = new TextFunnel();
    get_available_fonts();
}

Demo::~Demo() {}

// Private Members

void Demo::get_available_fonts()
{

    const char* path = "data/available_fonts.json";

    // If the file does not exist
    if(!debugger->file_exists(path))
    {
        debugger->log("[FAIL] Demo.get_available_fonts() -> Could not open"
            " file: ", true, false);
        debugger->log(path, false, true);
        debugger->log("[OUT] Exiting...");
        exit(0);
    }

    // Load the fonts into the engine
    file_stream.open(path, std::ios::in);

    if(file_stream.is_open())
    {
        file_stream >> j_loader;

        file_stream.close();
    }

    file_stream.clear();

    for(nlohmann::json::iterator it = j_loader.begin(); it != j_loader.end(); it++)
    {
        debugger->log("[OUT] Getting font: ", true, false);
        debugger->log(it.key(), false, true);
        font_paths[it.key()] = it.value();
    }

    file_stream.clear();

    if(font_paths.size() == 0)
    {
        debugger->log("[FAIL] No available fonts to use");
        debugger->log("[OUT] Exiting...");
        exit(0);
    }
}

void Demo::get_colors(const char* path)
{

    if(!debugger->file_exists(path))
    {
        debugger->log("[FAIL] Demo.load_colors() -> Could not open file: ", 
            true, false);
        debugger->log(path, false, true);
        debugger->log("[OUT] Exiting...");
        exit(0);
    }

    file_stream.open(path, std::ios::in);

    if(file_stream.is_open())
    {
        file_stream >> j_loader;

        file_stream.close();
    }

    file_stream.clear();

    for(nlohmann::json::iterator it = j_loader.begin(); it != j_loader.end(); 
        it++)
    {
        debugger->log("[OUT] Loading Color: ", true, false);
        debugger->log(std::string(it.key()), false, true);

        texture_handler->add_color(new Color(it.key(), it.value()[0], 
            it.value()[1], it.value()[2]));
    }
}

// Public Members

void Demo::display_colors()
{
    std::vector<std::string> colors = texture_handler->get_colors();
    SDL_Texture* temp_text = texture_handler->load_texture("assets/Sprites/border.png");
    SDL_Rect src, dest;

    src.x = 0;
    src.y = 0;
    src.w = 1;
    src.h = 1;

    full_window->clear();

    // Loop until the user presses Escape

    while(true)
    {
        frame_start = SDL_GetTicks64();

        SDL_RenderClear(renderer);

        for(int i = 0; i < colors.size(); i++)
        {

            dest.x = i * int(screen_width / colors.size());
            dest.y = 0;
            dest.w = int(screen_width / colors.size());
            dest.h = screen_height;

            texture_handler->draw(temp_text, src, dest, colors.at(i));
        }
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

void Demo::init(const char* title, int x, int y, int width, int height,
    bool fullscreen, int r, int g, int b)
{

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
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    }

    texture_handler = new TextureHandler(renderer, debugger);

    nlohmann::json jloader = Jloader::get("data/init.json");

    get_colors(static_cast<std::string>(jloader["color_path"]).c_str());

    debugger->log("[OUT] Creating Windows and Objects");

    // TextWindow
     text_window = new TextWindow(texture_handler, debugger,
         int(width / 2) + 1, width, 0, height, input_handler, 300);

    text_window->load_font(font_paths["ojae"].c_str());

    text_window->add("green", "Green");

    tilemap = new Tilemap(debugger, 15, 15);
    
    Entity* dirt = new Entity("Dirt");
    dirt->add_component<TransformComponent>();
    dirt->add_component<SpriteComponent>('~', "Brown", 1);
    tilemap->fill_tilemap(dirt);

    Entity* grass = new Entity("Grass");
    grass->add_component<TransformComponent>();
    grass->add_component<SpriteComponent>('~', "Green", 2);
    tilemap->fill_tilemap(grass);

    player = new Entity("Player");
    player->add_tag("PLAYER");
    player->add_component<TransformComponent>();
    player->add_component<SpriteComponent>('P', "Blue", 10);
    player->add_component<ColliderComponent>();
    player->add_script(new PlayerInput(input_handler));
    tilemap->add_entity(player, 10, 10);

    // Entity* goblin = new Entity("Goblin");
    // goblin->add_component<TransformComponent>();
    // goblin->add_component<SpriteComponent>('g', "Green", 9);
    // goblin->add_component<ColliderComponent>();
    // goblin->add_component<AIMovementComponent>(20);
    // goblin->add_script(new TrackEntity(player));
    // tilemap->add_entity(goblin, 1, 1);
    // tilemap->add_copy_entity(*goblin, 2, 1);

    Entity* troll = new Entity("Troll");
    troll->add_component<TransformComponent>();
    troll->add_component<SpriteComponent>('T', "Green", 9);
    troll->add_component<ColliderComponent>();
    troll->add_component<AIMovementComponent>(60);
    troll->add_script(new TrackEntity(player));
    tilemap->add_entity(troll, 13, 10);

    Entity* wizard = new Entity("Wizard");
    wizard->add_component<TransformComponent>();
    wizard->add_component<SpriteComponent>('w', "Purple", 9);
    wizard->add_component<ColliderComponent>();
    wizard->add_component<AIMovementComponent>(30);
    wizard->add_script(new AIRandomMovement(3));
    tilemap->add_entity(wizard, 2, 1);

    Entity* warrior = new Entity("Warrior");
    warrior->add_component<TransformComponent>();
    warrior->add_component<SpriteComponent>('w', "LGray", 9);
    warrior->add_component<ColliderComponent>();
    warrior->add_component<AIMovementComponent>(30);
    warrior->add_script(new AIRandomMovement(3));
    tilemap->add_entity(warrior, 3, 1);

    Entity* Elf = new Entity("Elf");
    Elf->add_component<TransformComponent>();
    Elf->add_component<SpriteComponent>('e', "Yellow", 9);
    Elf->add_component<ColliderComponent>();
    Elf->add_component<AIMovementComponent>(25);
    Elf->add_script(new AIRandomMovement(3));
    tilemap->add_entity(Elf, 5, 1);

    Entity* Dwarf = new Entity("Dwarf");
    Dwarf->add_component<TransformComponent>();
    Dwarf->add_component<SpriteComponent>('D', "Blue", 9);
    Dwarf->add_component<ColliderComponent>();
    Dwarf->add_component<AIMovementComponent>(30);
    Dwarf->add_script(new AIRandomMovement(3));
    tilemap->add_entity(Dwarf, 6, 1);
    
    Entity* stone_wall = new Entity("Stone Wall");
    stone_wall->add_component<SpriteComponent>('W', "LGray", 5);
    stone_wall->add_component<ColliderComponent>();
    tilemap->add_entity(stone_wall, 7, 8);
    tilemap->add_copy_entity(*stone_wall, 7, 7);
    tilemap->add_copy_entity(*stone_wall, 8, 7);
    
    // tilemap->add_entity(stone_wall, 1, 5);

    // for(int x = 2; x < 6; x++)
    // {
    //     tilemap->add_copy_entity(stone_wall, x, 5);
    // }

    //TilemapWindow
    tilemap_window = new TilemapWindow(texture_handler, debugger, tilemap,
        0, width / 2, 0, height, input_handler);

    tilemap_window->load_font(font_paths["ojae"].c_str());

    full_window = new TextWindow(texture_handler, debugger, 0, width, 0, 
        height, input_handler, -1);
    full_window->load_font(font_paths["ojae"].c_str());

    debugger->log("[OUT] Game Initialized");
}

void Demo::start()
{
    startup_screen();
    display_colors();
    running = true;
    execution_loop();
}

void Demo::startup_screen()
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

void Demo::execution_loop()
{
    while(running)
    {
        frame_start = SDL_GetTicks64();
        Uint64 start_time = SDL_GetTicks64();

        update();
        update_time = SDL_GetTicks64() - start_time;
        start_time = SDL_GetTicks64();

        handle_events();
        handle_events_time = SDL_GetTicks64() - start_time;
        start_time = SDL_GetTicks64();

        draw_all();
        draw_time = SDL_GetTicks64() - start_time;

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

    tilemap_window->update();
    text_window->clear();

    text_window->add("Update: ", "White", false);
    text_window->add(std::to_string(update_time), determine_color(update_time, 100));
    text_window->add("Handle Events: ", "White", false);
    text_window->add(std::to_string(handle_events_time), determine_color(handle_events_time, 100));
    text_window->add("Draw: ", "White", false);
    text_window->add(std::to_string(draw_time), determine_color(draw_time, 100));

    for(std::string element : text_funnel->get_contents())
    {
        text_window->add(element, "Blue");
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
