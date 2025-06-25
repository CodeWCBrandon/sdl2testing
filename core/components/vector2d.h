#pragma once
#include "../engine.h"

class Vector2d
{
    public:
        double xPos;
        double yPos;

        Vector2d(double xPos = 0, double yPos = 0);
        void Normalize();
};