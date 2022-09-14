#include <fstream>
#include <iostream>

#include "Demo.h"
#include "Objects/AllObjects.h"
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
    font_index = 0;
    debugger = new Debugger("OutputLog.txt");
    input_handler = new InputHandler();
    text_funnel = new TextFunnel();
    get_available_fonts();
}

Demo::~Demo() {}

// Private Members

void Demo::get_available_fonts()
{

    const char* path = "assets/available_fonts.json";

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
        std::string value = it.value();

        debugger->log("[OUT] Getting font: ", true, false);
        debugger->log(value, false, true);
        available_fonts.push_back(value);
        font_paths[value] = "assets/" + value  + "_font.json";
    }

    file_stream.clear();

    if(available_fonts.size() == 0)
    {
        debugger->log("[FAIL] No available fonts to use");
        debugger->log("[OUT] Exiting...");
        exit(0);
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
    get_colors("assets/colors.json");

    debugger->log("[OUT] Creating Handler Objects");

    // TextWindow
     text_window = new TextWindow(texture_handler, debugger,
         int(width / 2) + 1, width, 0, height, input_handler, 300);

    text_window->load_font(font_paths[available_fonts.at(font_index)].c_str());

    player = new Player(input_handler, text_funnel, "Player", 'P');

    tilemap = new Tilemap(input_handler, text_funnel, player, 10, 10);
    tilemap->fill_tilemap(new Tile("Floor", "White", '~', true, 0));
    tilemap->add(new Chest(text_funnel), 8, 8);

    //TilemapWindow
    tilemap_window = new TilemapWindow(texture_handler, debugger, tilemap,
        0, width / 2, 0, height, input_handler);

    tilemap_window->load_font(font_paths[available_fonts.at(font_index)].c_str());

    tilemap->add(player, 3, 3);

    text_window->add("Text", "Blue");

    debugger->log("[OUT] Game Initialized");
}

void Demo::start()
{
    running = true;
    execution_loop();
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

/**
 * @brief Executes the main simulation, at a target 60 fps */
void Demo::execution_loop()
{
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

    text_window->update();
    input_handler->update();

    tilemap->update_all_entities();
    tilemap->move_all_entities();
    tilemap->handle_keys();

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

void Demo::handle_keys()
{
    for(Key* key: input_handler->get_active_keys())
    {
        // f
        if(key->id == 102 && available_fonts.size() > 1)
        {
            font_index = (font_index + 1) % available_fonts.size();
            const char* targ_path = 
                font_paths[available_fonts.at(font_index)].c_str();

            text_window->add("Loading Font: ", "Blue", false);
            text_window->add(available_fonts.at(font_index), "Blue", true);

            text_window->load_font(targ_path);
            tilemap_window->load_font(targ_path);
            input_handler->set_delay(102, 30);
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
