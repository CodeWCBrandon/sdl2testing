#pragma once
#include "../engine.h"

class Vector2d
{
    public:
        double x;
        double y;
        double rotationAngle;

        Vector2d();
        Vector2d(double x, double y);
        Vector2d(double x, double y, double rotationAngle);
        void SetPosition(double x, double y);
        void SetRotation(double angle);
        static void Normalize(double& x, double& y);
};