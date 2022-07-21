#include "Demo.h"
#include "TextRenderer.h"

SDL_Window* Demo::window = nullptr;
SDL_Renderer* Demo::renderer = nullptr;
SDL_Event Demo::event;

bool Demo::running = false;

InputHandler* Demo::input_handler = nullptr;
TextRenderer* text_renderer = nullptr;

SDL_Texture* red_box = nullptr;
SDL_Rect red_box_src, red_box_dest;

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

    text_renderer = new TextRenderer(screen_width, screen_height);

    red_box = TextureHandler::load_texture("assets/red_box.png");

    red_box_src.x = 0;
    red_box_src.y = 0;
    red_box_src.w = 16;
    red_box_src.h = 16;

    red_box_dest.x = 50;
    red_box_dest.y = 50;
    red_box_dest.w = 32;
    red_box_dest.h = 32;

    text_renderer->clear();
    text_renderer->add("This is sample text");
    text_renderer->add_new_line();
    text_renderer->add("This is sample text after a new line");

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
                red_box_dest.y -= 3;
                break;

            case 's':
                red_box_dest.y += 3;
                break;

            case 'd':
                red_box_dest.x += 3;
                break;

            case 'a':
                red_box_dest.x -= 3;
                break;

            default:
                break;
        }
    }
}

void Demo::draw_all()
{
    SDL_RenderClear(renderer);

    text_renderer->draw_all();
    TextureHandler::draw(red_box, red_box_src, red_box_dest);

    SDL_RenderPresent(renderer);
}

void Demo::quit()
{
    SDL_Quit();
}
