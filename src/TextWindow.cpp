#include "TextWindow.h"

TextWindow::TextWindow() : BaseWindow()
{
    life_time = 0;
    input_handler = nullptr;
    text_renderer = nullptr;
}

TextWindow::TextWindow(int start_x, int end_x, int start_y, int end_y,
    InputHandler* input_handler, int life_time) : 
    BaseWindow(start_x, end_x, start_y, end_y, true)
{
    this->life_time = life_time;
    this->input_handler = input_handler;
    text_renderer = new TextRenderer(this->start_x, this->end_x, 
        this->start_y, this->end_y);
}

TextWindow::~TextWindow()
{
    delete text_renderer;
}

void TextWindow::update()
{
    /*
    Iterates through the content list, and checks if any member is exceeding 
    its lifetime. If so, it is deleted from the content list
    */

    Uint32 current_time = SDL_GetTicks();

    for(int i = 0; i < contents.size(); i++)
    {
        if(contents.at(i).second <= current_time)
        {
            contents.erase(contents.begin() + i);
            i--;
        }
    }
}

void TextWindow::display()
{
    /*
    Loops throught the contents, and adds text to the text renderer to render 
    to the screen
    */

    text_renderer->clear();

    int x_pos = start_x + border_size;
    int y_pos = start_y + border_size;
    int font = text_renderer->get_font();

    for(std::pair<std::string,Uint64> element : contents)
    {
        for(char c : element.first)
        {
            if(c == '\n')
            {
                y_pos += font * 1.5;
                x_pos = start_x + border_size;
                goto CHECK_Y_LIMIT;
            }

            text_renderer->add(c, x_pos, y_pos);
            x_pos += font;

            CHECK_Y_LIMIT:

            // If we try to render text to a part of the screen we can't see, 
            // exit 
            if(y_pos > end_y - border_size)
            {
                text_renderer->draw();
                return;
            }
        }
    }

    text_renderer->draw();
}

void TextWindow::add(std::string new_content)
{
    contents.insert(contents.begin(), 
        {new_content, SDL_GetTicks64() + life_time});
}

void TextWindow::clear()
{
    contents.clear();
}

void TextWindow::set_font(int font_size)
{
    text_renderer->set_font(font_size);
}