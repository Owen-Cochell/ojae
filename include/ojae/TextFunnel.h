#pragma once

#include <string>
#include <vector>

#include "Text.h"

class TextFunnel
{

private:

    std::vector<std::pair<std::string,std::string>> contents;

public:

    TextFunnel();
    ~TextFunnel();

    std::vector<std::pair<std::string,std::string>> get_contents();

    void add(std::string new_content, std::string color = "White");
    void clear();

};