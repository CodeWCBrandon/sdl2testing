#pragma once
#include "../engine.h"
#include "vector2d.h"

class Object
{
    public:
        SDL_Texture* texture;
        Vector2d pos;
        double width;
        double height;

        Object();
        Object(const char* texturePath, double xPos, double yPos, double width, double height);
        void Transform(double xPos, double yPos);
        void Scale(double width, double height);
        void SetTexture(const char* texturePath);

};