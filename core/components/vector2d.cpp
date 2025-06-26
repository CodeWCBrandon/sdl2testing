#include "vector2d.h"
#include <cmath>

Vector2d::Vector2d(double x = 0, double y = 0)
{
    this->x = x;
    this->y = y;
}

void Vector2d::Normalize(double& x, double& y)
{
    double magnitude = std::sqrt(x * x + y * y);

    if(magnitude > 0.00f)
    {
        x = x / magnitude;
        y = y / magnitude;
    }
}