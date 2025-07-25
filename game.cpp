#include "core/engine.h"
#include "core/components/object.h"
#include "core/components/vector2d.h"
#include "core/components/text.h"
#include "menu.h"

void PlayerMovement();
void HandlePlayerRotation();

class Player
{
    public: 
        Object* object;
        double speed;
};

Player player;
Text* score;

int currentScore = 0;

//Game logic
void Engine::Start()
{
    //assigning global variables value
    Object* background = new Object("assets/spacebg.bmp", 0, 0, windowLayout.w, windowLayout.h, 0);
    background->AddToRenderBuffer();

    //player
    player.object = new Object("assets/playerShip.bmp", windowLayout.w / 2, windowLayout.h / 2, 20, 20, 1);
    player.speed = 300;
    player.object->AddToRenderBuffer();

    //other stuff
    score = new Text("Score: " + std::to_string(currentScore), 25, 25, 100, 12, 2);
    score->SetFont("assets/fonts/ARCADE_N.TTF", 20);
    score->SetColor(255, 255, 255, 255);
    score->AddToRenderBuffer();
}

//Updating every frames
void Engine::Update()
{
    PlayerMovement();
    if(Engine::inputBuffer.count(SDLK_SPACE))
    {
        currentScore++;
        score->SetText("Score: " + std::to_string(currentScore));
    }

    HandlePlayerRotation();
}

void HandlePlayerRotation()
{
    double dx = Engine::mousePos.x - player.object->transform.x;
    double dy = Engine::mousePos.y - player.object->transform.y;

    double angle = std::atan2(dx, -dy) * (180.0 / M_PI);
    player.object->transform.rotationAngle = angle;
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
    player.object->Transform(player.object->transform.x + (xDir * player.speed * Engine::deltaTime), 
                             player.object->transform.y + (yDir * player.speed * Engine::deltaTime));
}