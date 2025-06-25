#include "object.h"
#include "vector2d.h"

Object::Object(double xPos, double yPos, double width, double height) : pos(xPos, yPos)
{
    this->width = width;
    this->height = height;
}

void Object::Transform(double xPos, double yPos)
{
    this->pos.xPos = xPos;
    this->pos.yPos = yPos;
}

void Object::Scale(double width, double height)
{
    this->width = width;
    this->height = height;
}