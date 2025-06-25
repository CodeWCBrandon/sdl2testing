#pragma once
#include "../engine.h"
#include "vector2d.h"

class Object
{
    public:
        Vector2d pos;
        double width;
        double height;

        Object();
        Object(double xPos, double yPos, double width, double height);
        void Transform(double xPos, double yPos);
        void Scale(double width, double height);

};