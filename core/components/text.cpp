#include <string>
#include "text.h"

Text::Text() : Entity(0, 0, 0, 0, 0){}

Text::Text(std::string text, double xPos, double yPos, double width, double height, int layerMask) :
Entity(xPos, yPos, width, height, layerMask)
{
    this->text = text;
    UpdateRectFormat();
}

Text::~Text()
{
    // text destroyed
}

void Text::SetText(std::string text)
{
    this->text = text;
    SetTexture();
}

void Text::SetColor(int red, int green, int blue, int alpha)
{
    this->color.r = red;
    this->color.g = green;
    this->color.b = blue;
    this->color.a = alpha;
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
    if(texture) SDL_DestroyTexture(texture);
    if(!font)
    {
        std::cout << "font is not loaded yet\n";
        return;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    texture = Engine::LoadTexture(textSurface);
    // SDL_FreeSurface(textSurface);
}
