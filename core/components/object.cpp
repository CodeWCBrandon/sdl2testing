#include "object.h"

Object::Object(double xPos, double yPos, double width, double height) : pos(xPos, yPos)
{
    this->width = width;
    this->height = height;
}