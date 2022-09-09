#include "TextFunnel.h"

TextFunnel::TextFunnel() {}

TextFunnel::~TextFunnel() {}

std::vector<std::string> TextFunnel::get_contents() { return contents; }

void TextFunnel::add(std::string new_content)
{
    contents.push_back(new_content);
}

void TextFunnel::clear()
{
    contents.clear();
}