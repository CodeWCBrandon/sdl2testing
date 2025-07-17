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
    player.object = new Object("assets/playerShip.bmp",windowLayout.w / 2, windowLayout.h / 2, 20, 20, 1);
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
    HandlePlayerRotation();
    if(Engine::inputBuffer.count(SDLK_SPACE))
    {
        currentScore++;
        score->SetText("Score: " + std::to_string(currentScore));
    }
}

void HandlePlayerRotation()
{
    double dx = Engine::mousePos.x - player.object->transform.x;
    double dy = Engine::mousePos.y - player.object->transform.y;

    double angle = std::atan2(dx, -dy) * (180.0 / 3.14);
    player.object->transform.rotationAngle = angle;
}

void PlayerMovement()
{
    double yDir = 0;
    double xDir = 0;

    static double xCurrentSpeed = 0, yCurrentSpeed = 0;

    double xTargetSpeed, xSpeedDiff, xForce;
    double yTargetSpeed, ySpeedDiff, yForce;

    double accelRate = 2.0f;
    double decelRate = 2.0f;

    if(Engine::inputBuffer.count(SDLK_w)) yDir += -1.0f;
    if(Engine::inputBuffer.count(SDLK_a)) xDir += -1.0f;
    if(Engine::inputBuffer.count(SDLK_s)) yDir += 1.0f;
    if(Engine::inputBuffer.count(SDLK_d)) xDir += 1.0f;

    Vector2d::Normalize(xDir, yDir);
    
    // Hanlde  X input
    if(xDir != 0){
        // Amount of force scaled with how close the current speed is to maximum/target
        xTargetSpeed = player.speed * xDir;
        xSpeedDiff = xTargetSpeed - xCurrentSpeed;

        xForce = xSpeedDiff * accelRate * Engine::deltaTime;
        xCurrentSpeed += xForce;
    }else{
        // No input means the target speed is 0 (stationary)
        xTargetSpeed = 0;
        xSpeedDiff = xCurrentSpeed;

        xForce = xSpeedDiff * decelRate * Engine::deltaTime;
        xCurrentSpeed -= xForce;
    }

    // Handle Y ionput (same as x input)
    if(yDir != 0){
        // Amount of force scaled with how close the current speed is to maximum/target
        yTargetSpeed = player.speed * yDir;
        ySpeedDiff = yTargetSpeed - yCurrentSpeed;

        yForce = ySpeedDiff * accelRate * Engine::deltaTime;
        yCurrentSpeed += yForce;
    }else{
        // No input means the target speed is 0 (stationary)
        yTargetSpeed = 0;
        ySpeedDiff = yCurrentSpeed;

        yForce = ySpeedDiff * decelRate * Engine::deltaTime;
        yCurrentSpeed -= yForce;
    }
    // std::cout << xCurrentSpeed << " " << xDir << std::endl;

    // Clamp very small speeds to 0
    if(abs(xCurrentSpeed) < 0.0001) xCurrentSpeed = 0;
    if(abs(yCurrentSpeed) < 0.0001) yCurrentSpeed = 0;

    player.object->Transform(player.object->transform.x + (xCurrentSpeed * Engine::deltaTime), 
                             player.object->transform.y + (yCurrentSpeed * Engine::deltaTime));
}
