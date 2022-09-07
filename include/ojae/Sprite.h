#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "TextureHandler.h"


/**
 * @brief Stores data for each object when it is rendered to the screen, for instance
    storing a texture, SDL Rects for renderering and position
 * 
 */
class Sprite
{
private:

    SDL_Rect src, dest;
    SDL_Texture* texture;
    TextureHandler* texture_handler; // Instance of the TextureHandler

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

    Sprite(TextureHandler* _texture_handler, const char* path, int src_x, int src_y, int src_w, 
        int src_h, int dest_x, int dest_y, int dest_w, int dest_h)
    {
        texture_handler = _texture_handler;
        texture = texture_handler->load_texture(path);

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

    int get_width() { return dest.w; }

    int get_height() { return dest.h; }

    void set_position(int x, int y)
    {
        /*
        Sets the new position of the sprite

        :PARAM x: X Coordinate to render the sprite at 
        :PARAM y: Y Coordinate to render the sprite
        */

        dest.x = x;
        dest.y = y; 
    }

    void draw()
    {
        /*
        Draws the texture to the screen
        */

        texture_handler->draw(texture, src, dest);
    }
};
