#pragma once
#include "../engine.h"
#include "vector2d.h"

class Object
{
    public:
        SDL_Texture* texture;
        SDL_Rect rectFormat;
        Vector2d position;
        double width;
        double height;
        int layerMask;

        Object();
        Object(const char* texturePath, double xPos, double yPos, double width, double height, int layerMask);
        void Transform(double xPos, double yPos);
        void Scale(double width, double height);
        void SetTexture(const char* texturePath);
        void SetLayerMask(int layerMask);
        void UpdateRectFormat();
        void AddToRenderBuffer();
};