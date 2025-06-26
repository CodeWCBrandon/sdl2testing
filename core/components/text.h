#pragma once
#include <string>
#include "../engine.h"
#include "entity.h"

class Text : public Entity
{
    public:
        std::string text;
        int red;
        int green;
        int blue;
        int alpha;

        Text();
        Text(std::string text, double xPos, double yPos, double width, double height, int layerMask);

        void SetText(std::string text, int red, int green, int blue, int alpha);
        void SetColor(int red, int green, int blue, int alpha);
        void InitText();
        void SetTexture();
};