#pragma once

#include <string>


struct Text
{
    std::string content; // Contents of the text
    std::string color; // Color of the text

    /**
     * @brief // Number of frames this key will be rendered until removed from
     * the contents
     */
    int life_time; 

    Text() 
    {
        life_time = 0;
    }

    Text(std::string _content, std::string _color, int _life_time)
    {
        content = _content;
        color =_color;
        life_time = _life_time;
    }

    ~Text() {}
};