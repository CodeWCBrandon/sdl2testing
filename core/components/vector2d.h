#pragma once
#include "../engine.h"

class Vector2d
{
    public:
        double xPos;
        double yPos;

        Vector2d(double, double);
        void Normalize();
};