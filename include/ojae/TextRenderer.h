#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include <vector>
#include <string>

#include "TextureHandler.h"

class TextRenderer
{
    /*
    Handles the drawing of text to the SDL Window
    */

private:

    SDL_Rect src, dest;
    SDL_Texture* texture;

    std::string path; // Path to the current character png

    int font; // Font size of the text being displayed
    std::pair<int, int> cursor_pos; // Position of the cursor in the window

    std::vector<int> available_fonts; // List of available fonts 
    std::vector<std::string> contents; // List of the content to render

    int screen_width;
    int screen_height;

public:

    TextRenderer();
    TextRenderer(int screen_width, int screen_height);
    ~TextRenderer();

    void add(std::string new_content);
    void add(std::string new_content, int amount);
    void add_new_line(int amount = 1);
    void clear();
    void set_font(int font_size);
    void draw_all();
};