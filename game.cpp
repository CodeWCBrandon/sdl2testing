#include "core/engine.h"
#include "core/components/object.h"
#include "core/components/vector2d.h"

void PlayerMovement();

class Player
{
    public: 
        Object* object;
        double speed;
};

Player player;


//Game logic
void Engine::Start()
{
    //assigning global variables value
    Object* background = new Object("assets/spacebg.bmp", 0, 0, windowLayout.w, windowLayout.h, 0);
    background->AddToRenderBuffer();
    player.object = new Object("assets/playerShip.bmp", windowLayout.w / 2, windowLayout.h / 2, 20, 20, 1);
    player.speed = 3;
    player.object->AddToRenderBuffer();

    //other stuff

    
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
    double yDir = 0;
    double xDir = 0;

    if(Engine::inputBuffer.count(SDLK_w)) yDir = -1;
    if(Engine::inputBuffer.count(SDLK_a)) xDir = -1;
    if(Engine::inputBuffer.count(SDLK_s)) yDir = 1;
    if(Engine::inputBuffer.count(SDLK_d)) xDir = 1;

    Vector2d::Normalize(xDir, yDir);
    player.object->Transform(player.object->position.x + (xDir * player.speed), player.object->position.y + (yDir * player.speed));
}