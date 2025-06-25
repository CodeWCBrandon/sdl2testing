#pragma once
#include "../engine.h"

class Vector2d
{
    public:
        int xPos;
        int yPos;

        Vector2d(int xPos, int yPos);
        void Normalize();
};