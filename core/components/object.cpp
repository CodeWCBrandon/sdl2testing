#include "object.h"

Object::Object(SDL_Texture* texture, double xPos, double yPos, double width, double height) : pos(xPos, yPos)
{
    this->texture = texture;
    this->width = width;
    this->height = height;
}