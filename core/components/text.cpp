#include <string>
#include "text.h"

Text::Text() : Entity(0, 0, 0, 0, 0){}

Text::Text(std::string text, double xPos, double yPos, double width, double height, int layerMask) :
Entity(xPos, yPos, width, height, layerMask), red(0), green(0), blue(0)
{
    this->text = text;
}

void Text::SetText(std::string text, int red, int green, int blue, int alpha)
{
    this->text = text;
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = alpha;
}

void Text::SetColor(int red, int green, int blue, int alpha)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = alpha;
}

void Text::SetTexture()
{
    SDL_Surface* textSurface;
    SDL_Color color;

    color.r = red;
    color.g = green;
    color.b = blue;
    color.a = alpha;
    
}
