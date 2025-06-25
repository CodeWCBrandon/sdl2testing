#include "core/engine.h"

void PlayerMovement();

// ========= VARIABLES ==========
SDL_Texture* background;
SDL_Rect player = {50, 50, 20, 20};

//Game logic
void Engine::Start()
{
    //adding backgrounds
    SDL_Surface* tempBG = SDL_LoadBMP("spacebg.bmp");
    background = SDL_CreateTextureFromSurface(renderer, tempBG);
    SDL_FreeSurface(tempBG); // flushing temp Background    
    
    //centering player
    player.x = (windowLayout.w - player.w) / 2;
    player.y = (windowLayout.h - player.h) / 2;
}

//Updating every frames
bool Engine::Update()
{
    SDL_RenderCopy(renderer, background, NULL, &windowLayout); // render image
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