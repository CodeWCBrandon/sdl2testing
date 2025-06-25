#include "core/engine.h"

void PlayerMovement();

// ========= VARIABLES ==========
SDL_Rect player = {50, 50, 20, 20};
Object background = Object(0, 0, 840, 600);

//Game logic
void Engine::Start()
{
    //centering player
    player.x = (windowLayout.w - player.w) / 2;
    player.y = (windowLayout.h - player.h) / 2;
}

//Updating every frames
bool Engine::Update()
{
    Engine::RenderTexture(Engine::renderer, "assets/spacebg.bmp", background);
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