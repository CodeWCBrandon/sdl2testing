#pragma once
#include <string>
#include "../engine.h"
#include "entity.h"

class Text : public Entity
{
    public:


        Text();
        Text(std::string text, double xPos, double yPos, double width, double height, int layerMask);
        void loadText();
};