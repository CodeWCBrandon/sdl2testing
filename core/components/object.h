#pragma once
#include "../engine.h"
#include "vector2d.h"

class Object
{
    public:
        Vector2d pos;
        double width;
        double height;

        Object(double xPos, double yPos, double width, double height);

};