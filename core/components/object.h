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

        Object(SDL_Texture*, double, double, double, double);

};