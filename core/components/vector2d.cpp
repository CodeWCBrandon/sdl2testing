#include "vector2d.h"
#include <cmath>

Vector2d::Vector2d(double xPos, double yPos)
{
    this->xPos = xPos;
    this->yPos = yPos;
}

void Vector2d::Normalize()
{
    double magnitude = std::sqrt(xPos * xPos + yPos * yPos);

    if(magnitude > 0.00f)
    {
        this->xPos = this->xPos / magnitude;
        this->yPos = this->yPos / magnitude;
    }
}