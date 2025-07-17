#include "vector2d.h"
#include <cmath>

Vector2d::Vector2d() : x(0), y(0), rotationAngle(0) {}

Vector2d::Vector2d(double x = 0, double y = 0, double rotationAngle = 0.0f)
{
    this->x = x;
    this->y = y;
    this->rotationAngle = rotationAngle;
}

Vector2d::Vector2d(double x = 0, double y = 0)
{
    this->x = x;
    this->y = y;
    this->rotationAngle = 0.0f;
}

void Vector2d::SetPosition(double x, double y)
{
    this->x = x;
    this->y = y;
}

void Vector2d::SetRotation(double angle)
{
    this->rotationAngle = angle;
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