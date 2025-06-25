#include "core/engine.h"
#include "core/components/object.h"
#include "core/components/vector2d.h"

void PlayerMovement();

Object player;

//Game logic
void Engine::Start()
{
    //assigning global variables value
    Object background("assets/spacebg.bmp", 0, 0, Engine::windowLayout.w, Engine::windowLayout.h, 0);
    background.AddToRenderBuffer();
    player.SetTexture("assets/playerShip.bmp"); player.Transform(windowLayout.w / 2, windowLayout.h / 2);
    player.Scale(20, 20);
    player.AddToRenderBuffer();
    
}

//Updating every frames
bool Engine::Update()
{
    PlayerMovement();
    
    //processes
    if(Engine::inputBuffer.count(SDLK_ESCAPE)) return false;
    return true; // keep looping
}

void PlayerMovement()
{
    if(Engine::inputBuffer.count(SDLK_w)) player.pos.yPos -= 5;
    if(Engine::inputBuffer.count(SDLK_a)) player.pos.xPos -= 5;
    if(Engine::inputBuffer.count(SDLK_s)) player.pos.yPos += 5;
    if(Engine::inputBuffer.count(SDLK_d)) player.pos.xPos += 5;
}