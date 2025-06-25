#include "core/engine.h"
#include "core/components/object.h"
#include "core/components/vector2d.h"

void PlayerMovement();

// ========= VARIABLES ==========
SDL_Rect player = {50, 50, 20, 20};

//Game logic
void Engine::Start()
{
    //assigning global variables value
    Object background("assets/spacebg.bmp", 0, 0, Engine::windowLayout.w, Engine::windowLayout.h, 0);
    background.AddToRenderBuffer();
    
    //centering player
    player.x = (windowLayout.w - player.w) / 2;
    player.y = (windowLayout.h - player.h) / 2;
}

//Updating every frames
bool Engine::Update()
{
    Engine::RenderTexture();
    RenderRect(renderer, player, 0, 255, 255, 255);
    PlayerMovement();
    
    //processes
    if(Engine::inputBuffer.count(SDLK_ESCAPE)) return false;
    return true; // keep looping
}

void PlayerMovement()
{
    if(Engine::inputBuffer.count(SDLK_w)) player.y -= 5;
    if(Engine::inputBuffer.count(SDLK_a)) player.x -= 5;
    if(Engine::inputBuffer.count(SDLK_s)) player.y += 5;
    if(Engine::inputBuffer.count(SDLK_d)) player.x += 5;
}