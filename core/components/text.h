#pragma once
#include <string>
#include "../engine.h"
#include "entity.h"

class Text : public Entity
{
    public:
        TTF_Font* font;
        SDL_Color color;
        std::string text;

        Text();
        Text(std::string text, double xPos, double yPos, double width, double height, int layerMask);
        virtual ~Text();

        void SetFont(const char* fontPath, int fontSize);
        void SetText(std::string text);
        void SetColor(int red, int green, int blue, int alpha);
        void SetTexture();
};