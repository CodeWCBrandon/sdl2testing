#include <string>
#include "text.h"

Text::Text() : Entity(0, 0, 0, 0, 0){}

Text::Text(std::string text, double xPos, double yPos, double width, double height, int layerMask) :
Entity(xPos, yPos, width, height, layerMask), red(0), green(0), blue(0)
{
    this->text = text;
    UpdateRectFormat();
}

void Text::SetText(std::string text)
{
    this->text = text;
    SetTexture();
}

void Text::SetColor(int red, int green, int blue, int alpha)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = alpha;
    SetTexture();
}

void Text::SetFont(const char* fontPath, int fontSize)
{
    this->font = TTF_OpenFont(fontPath, fontSize);
    if(!font)
    {
        std::cout << "Failed to load font: " << fontPath << TTF_GetError() << std::endl;
        return;
    }
    SetTexture();
}

void Text::SetTexture()
{
    if(!font)
    {
        std::cout << "font is not loaded yet\n";
        return;
    }

    SDL_Surface* textSurface;
    SDL_Color color;

    color.r = red;
    color.g = green;
    color.b = blue;
    color.a = alpha;

    textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    texture = Engine::LoadTexture(textSurface);
}
