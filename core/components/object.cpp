#include "object.h"
#include "vector2d.h"

//default constructor
Object::Object() : position(0, 0), width(0), height(0), layerMask(0) {}

//constructor
Object::Object(const char* texturePath, double x = 0, double y = 0, double width = 0, double height = 0, int layerMask = 0) : position(x, y)
{
    this->texture = Engine::LoadTexture(texturePath);
    this->width = width;
    this->height = height;
    this->layerMask = layerMask;

    rectFormat.h = height;
    rectFormat.w = width;
    rectFormat.x = x;
    rectFormat.y = y;
}

void Object::Transform(double x, double y)
{
    this->position.x = x;
    this->position.y = y;

    rectFormat.x = x;
    rectFormat.y = y;

    UpdateRectFormat();
}

void Object::Scale(double width, double height)
{
    this->width = width;
    this->height = height;

    rectFormat.h = height;
    rectFormat.w = width;
    
    UpdateRectFormat();
}

void Object::UpdateRectFormat()
{
    this->rectFormat.h = height;
    this->rectFormat.w = width;
    this->rectFormat.x = position.x;
    this->rectFormat.y = position.y;
}

void Object::SetTexture(const char* texturePath)
{
    this->texture = Engine::LoadTexture(texturePath);
}

void Object::SetLayerMask(int layerMask)
{
    this->layerMask = layerMask;
}

void Object::AddToRenderBuffer()
{
    Engine::AddToRenderBuffer(this);
}