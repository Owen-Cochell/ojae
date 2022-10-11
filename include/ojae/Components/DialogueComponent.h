#pragma once 

#include <string>

#include "../ECS.h"
#include "../TextFunnel.h"

struct DialogueComponent : public Component
{
    TextFunnel* text_funnel;

    DialogueComponent(TextFunnel* _text_funnel) 
    {
        text_funnel = _text_funnel;
    }

    Component* clone() override
    {
        return new DialogueComponent(text_funnel);
    }
};
