#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "TextureHandler.h"

class Sprite
{

private:

    SDL_Rect src, dest;
    SDL_Texture* texture;

public:

    Sprite() 
    {
        src.x = 0;
        src.y = 0;
        src.w = 0;
        src.h = 0;

        dest.x = 0;
        dest.y = 0;
        dest.w = 0;
        dest.h = 0;
    }

    Sprite(int src_x, int src_y, int src_w, int src_h, int dest_x, int dest_y,
        int dest_w, int dest_h, const char* path)
    {
        texture = TextureHandler::load_texture(path);

        src.x = src_x;
        src.y = src_y;
        src.w = src_w;
        src.h = src_h;

        dest.x = dest_x;
        dest.y = dest_y;
        dest.w = dest_w;
        dest.h = dest_h;
    }

    ~Sprite() 
    {
        SDL_DestroyTexture(texture);
    }

    void set_position(int x, int y)
    {
        dest.x = x;
        dest.y = y; 
    }

    void draw()
    {
        TextureHandler::draw(texture, src, dest);
    }
};