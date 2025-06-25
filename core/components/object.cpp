#include "object.h"
#include "vector2d.h"

//default constructor
Object::Object() : pos(0, 0), width(0), height(0) {}

//constructor
Object::Object(double xPos = 0, double yPos = 0, double width = 0, double height = 0) : pos(xPos, yPos)
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