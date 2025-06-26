#include "object.h"
#include "vector2d.h"

//default constructor
Object::Object() : Entity(0, 0, 0, 0, 0) {}

//constructor
Object::Object(const char* texturePath, double x = 0, double y = 0, double width = 0, double height = 0, int layerMask = 0) : 
Entity(x, y, width, height, layerMask)
{
    SetTexture(texturePath);
    UpdateRectFormat();
}

void Object::SetTexture(const char* texturePath)
{
    SDL_Surface* surface = SDL_LoadBMP(texturePath);
    texture = Engine::LoadTexture(surface);
    
    if(!texture)
    {
        std::cout << "failed to load texture: " << texturePath << "\n";
        return;
    }
    std::cout << texturePath << " loaded\n"; 
}