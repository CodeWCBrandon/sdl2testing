#include "core/engine.h"
#include "core/components/object.h"
#include "core/components/vector2d.h"

void PlayerMovement();

//Game logic
void Engine::Start()
{
    //assigning global variables value
    Object background("assets/spacebg.bmp", 0, 0, Engine::windowLayout.w, Engine::windowLayout.h, 0);
    background.AddToRenderBuffer();
    Object player("assets/playerShip.bmp", windowLayout.w / 2, windowLayout.h / 2, 20, 20, 1);
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
    // if(Engine::inputBuffer.count(SDLK_w)) player.y -= 5;
    // if(Engine::inputBuffer.count(SDLK_a)) player.x -= 5;
    // if(Engine::inputBuffer.count(SDLK_s)) player.y += 5;
    // if(Engine::inputBuffer.count(SDLK_d)) player.x += 5;
}