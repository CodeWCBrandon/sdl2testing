#include "entity.h"

Entity::Entity(double x, double y, double width, double height, int layerMask) : 
transform(x, y), width(width), height(height), layerMask(layerMask)
{

}

void Entity::Transform(double x, double y)
{
    this->transform.x = x;
    this->transform.y = y;

    rectFormat.x = x;
    rectFormat.y = y;

    UpdateRectFormat();
}

void Entity::Scale(double width, double height)
{
    this->width = width;
    this->height = height;

    rectFormat.h = height;
    rectFormat.w = width;
    
    UpdateRectFormat();
}

void Entity::UpdateRectFormat()
{
    this->rectFormat.h = height;
    this->rectFormat.w = width;
    this->rectFormat.x = transform.x;
    this->rectFormat.y = transform.y;
}

void Entity::SetLayerMask(int layerMask)
{
    this->layerMask = layerMask;
}

void Entity::AddToRenderBuffer()
{
    Engine::AddToRenderBuffer(this);
}

