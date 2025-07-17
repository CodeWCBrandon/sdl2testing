#pragma once
#include "../engine.h"
#include "vector2d.h"

class Entity
{
    public:
        SDL_Texture* texture;
        SDL_Rect rectFormat;
        Vector2d transform;
        double width;
        double height;
        int layerMask;

        Entity(double x, double y, double width, double height, int layerMask);
        virtual void Transform(double xPos, double yPos);
        virtual void Scale(double width, double height);
        virtual void SetLayerMask(int layerMask);
        virtual void UpdateRectFormat();
        virtual void AddToRenderBuffer();
};