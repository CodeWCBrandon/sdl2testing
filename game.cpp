#include "core/engine.h"
#include "core/components/object.h"
#include "core/components/vector2d.h"

void PlayerMovement();

Object* player;

//Game logic
void Engine::Start()
{
    //assigning global variables value
    Object* background = new Object("assets/spacebg.bmp", 0, 0, windowLayout.w, windowLayout.h, 0);
    background->AddToRenderBuffer();
    player = new Object("assets/playerShip.bmp", windowLayout.w / 2, windowLayout.h / 2, 20, 20, 1);
    player->AddToRenderBuffer();
    
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
    if(Engine::inputBuffer.count(SDLK_w)) player->Transform(player->position.x, player->position.y - 5);
    if(Engine::inputBuffer.count(SDLK_a)) player->Transform(player->position.x - 5, player->position.y);
    if(Engine::inputBuffer.count(SDLK_s)) player->Transform(player->position.x, player->position.y + 5);
    if(Engine::inputBuffer.count(SDLK_d)) player->Transform(player->position.x + 5, player->position.y);
}