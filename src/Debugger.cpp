#include <SDL2/SDL.h>
#include <string>

#include "Debugger.h"

// Constructors/Deconstructors 

Debugger::Debugger()
{
    path = "";
    clear();
}

Debugger::Debugger(const char* _path)
{
    path = _path;
    clear();
}

Debugger::~Debugger() {}

// Private Functions

void Debugger::dump(std::string content, bool output_time, bool new_line)
{
    file_stream.open(path, std::ios::app);

    if(file_stream.is_open())
    {
        if(output_time)
        {
            file_stream << SDL_GetTicks64();
            file_stream << " ms: ";
        }

        file_stream << content;

        if(new_line)
        {
            file_stream << '\n';
        }

        file_stream.close();
    }

    file_stream.clear();
}

// Public Functions

void Debugger::log(const char* content, bool output_time, bool new_line)
{
    dump(std::string(content), output_time, new_line);
}

void Debugger::log(char content, bool output_time, bool new_line)
{
    dump(std::string{content}, output_time,  new_line);
}

void Debugger::log(std::string content, bool output_time, bool new_line)
{
    dump(content, output_time,  new_line);
}

void Debugger::log(int content, bool output_time, bool new_line)
{
    dump(std::to_string(content), output_time,  new_line);
}

void Debugger::log(size_t content, bool output_time, bool new_line)
{
    dump(std::to_string(content), output_time,  new_line);
}

void Debugger::clear()
{
    file_stream.open(path, std::ios::out);
    file_stream.close();
    file_stream.clear();
}

bool Debugger::file_exists(const char* path)
{

    FILE *fp = fopen(path, "r");
    bool is_exist = false;
    if (fp != NULL)
    {
        is_exist = true;
        fclose(fp); // close the file
    }
    return is_exist;
}