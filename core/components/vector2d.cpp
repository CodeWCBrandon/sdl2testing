#include "vector2d.h"
#include <cmath>

Vector2d::Vector2d(double x = 0, double y = 0)
{
    this->x = x;
    this->y = y;
}

void Vector2d::Normalize()
{
    double magnitude = std::sqrt(x * x + y * y);

    if(magnitude > 0.00f)
    {
        this->x = this->x / magnitude;
        this->y = this->y / magnitude;
    }
}