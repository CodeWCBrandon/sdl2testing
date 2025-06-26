#pragma once
#include "../engine.h"

class Vector2d
{
    public:
        double x;
        double y;

        Vector2d(double x, double y);
        static void Normalize(double& x, double& y);
};