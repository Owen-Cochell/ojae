#include "TextFunnel.h"

TextFunnel::TextFunnel() {}

TextFunnel::~TextFunnel() {}

std::vector<std::pair<std::string,std::string>> TextFunnel::get_contents() { return contents; }

void TextFunnel::add(std::string new_content, std::string color)
{
    contents.push_back(
        std::pair<std::string,std::string>{new_content, color});
}

void TextFunnel::clear()
{
    contents.clear();
}