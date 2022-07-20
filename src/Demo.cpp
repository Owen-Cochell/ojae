#include "Demo.h"
#include "Debug.h"

SDL_Window* Demo::window = nullptr;
SDL_Renderer* Demo::renderer = nullptr;
SDL_Event Demo::event;

bool Demo::running = false;

InputHandler* Demo::input_handler = nullptr;

SDL_Texture* red_box = nullptr;
SDL_Rect src, dest;

Demo::Demo() {}

Demo::~Demo() {}

void Demo::init(const char* title, int x, int y, int width, int height,
    bool fullscreen)
{

    int flags = 0;

    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = SDL_CreateWindow(title, x, y, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 100, 100, 165, 255);
    }

    input_handler = new InputHandler();

    red_box = TextureHandler::load_texture("assets/red_box.png");

    src.x = 0;
    src.y = 0;
    src.w = 16;
    src.h = 16;

    dest.x = 50;
    dest.y = 50;
    dest.w = 32;
    dest.h = 32;

}

void Demo::start()
{
    running = true;
    execution_loop();
}

void Demo::execution_loop()
{
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
                dest.y -= 3;
                break;

            case 's':
                dest.y += 3;
                break;

            case 'd':
                dest.x += 3;
                break;

            case 'a':
                dest.x -= 3;
                break;

            default:
                break;
        }
    }
}

void Demo::draw_all()
{
    SDL_RenderClear(renderer);

    TextureHandler::draw(red_box, src, dest);

    SDL_RenderPresent(renderer);
}

void Demo::quit()
{
    SDL_Quit();
}
