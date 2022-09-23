#include <fstream>
#include <iostream>

#include "Demo.h"
#include "Player.h"
#include "TextRenderer.h"
#include "TextureHandler.h"
#include "TextWindow.h"
#include "TilemapWindow.h"
#include "TextFunnel.h"
#include "Objects/Chest.h"

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

Player* player; 

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
    get_colors("data/colors.json");

    debugger->log("[OUT] Creating Handler Objects");

    // TextWindow
     text_window = new TextWindow(texture_handler, debugger,
         int(width / 2) + 1, width, 0, height, input_handler, 300);

    text_window->load_font(font_paths["ojae"].c_str());

    text_window->add("green", "Green");

    player = new Player(input_handler, text_funnel, "Player", 'P');

    tilemap = new Tilemap(input_handler, text_funnel, debugger, player, 10, 10);
    tilemap->fill_tilemap(new Tile("Floor", "White", '.', true, 0));
    tilemap->add(new Chest(text_funnel), 8, 8);
    tilemap->add(new Tile("Apple", "Red", 'a', true, 2), 2, 2);
    tilemap->add(new Tile("Goblin", "Green", 'g', true, 2), 7, 2);
    tilemap->add(new Tile("Gold", "Yellow", 'G', true, 2), 2, 7);
    tilemap->add(player, 3, 3);

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
    running = true;
    execution_loop();
}

void Demo::startup_screen()
{   
    full_window->add("OJAE (Owen-Joel ASCII ENGINE)", "White");
    full_window->add("Version: ", "White", false);
    full_window->add("0.2 (Beta)", "White");

    std::map<std::string, Color*> active_colors = texture_handler->get_colors(); 

    for(std::map<std::string, Color*>::iterator it = active_colors.begin();
        it != active_colors.end(); it++)
    {
        full_window->add(it->first, it->first);
    }

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

        update();
        handle_events();
        // handle_keys();
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

    player->handle_keys();

    for(std::string element : text_funnel->get_contents())
    {
        text_window->add(element, "Green");
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

void Demo::handle_keys() {}

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
