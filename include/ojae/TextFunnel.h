#pragma once

#include <string>
#include <vector>

class TextFunnel
{

private:

    std::vector<std::string> contents;

public:

    TextFunnel();
    ~TextFunnel();

    std::vector<std::string> get_contents();

    void add(std::string new_content);
    void clear();

};