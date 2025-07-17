#pragma once
#include "../engine.h"
#include "entity.h"
#include "vector2d.h"

class Object : public Entity
{
    public:
        Object();
        Object(const char* texturePath, double xPos, double yPos, double width, double height, int layerMask);
        
        void SetTexture(const char* texturePath);
};