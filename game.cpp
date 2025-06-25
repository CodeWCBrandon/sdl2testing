#include "core/engine.h"
#include "core/components/object.h"
#include "core/components/vector2d.h"

void PlayerMovement();

// ========= VARIABLES ==========
SDL_Rect player = {50, 50, 20, 20};
Object background(0, 0, 1920, 1080);
SDL_Texture* backgroundTexture = Engine::LoadTexture(Engine::renderer, "assets/spacebg.bmp");

//Game logic
void Engine::Start()
{
    //load manually
    SDL_Surface* temp = SDL_LoadBMP("assets/spacebg.bmp");
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, temp);
    SDL_FreeSurface(temp);

    //centering player
    player.x = (windowLayout.w - player.w) / 2;
    player.y = (windowLayout.h - player.h) / 2;
}

//Updating every frames
bool Engine::Update()
{
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &windowLayout);
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