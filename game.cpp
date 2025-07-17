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

    static double xLastDir = 0, yLastDir = 0;
    static double xCurrentSpeed = 0, yCurrentSpeed = 0;
    int accelRate = 400;
    int decelRate = 200;

    if(Engine::inputBuffer.count(SDLK_w)) yDir += -1.0f;
    if(Engine::inputBuffer.count(SDLK_a)) xDir += -1.0f;
    if(Engine::inputBuffer.count(SDLK_s)) yDir += 1.0f;
    if(Engine::inputBuffer.count(SDLK_d)) xDir += 1.0f;

    Vector2d::Normalize(xDir, yDir);

    // Input in X axis
    if(xDir != 0 ){
        xLastDir = xDir;

        if(abs(xCurrentSpeed) < player.speed) xCurrentSpeed += accelRate * xDir * Engine::deltaTime;
        if(abs(xCurrentSpeed) > player.speed) xCurrentSpeed = player.speed * xDir;
    }else{
        if(abs(xCurrentSpeed) > 0) xCurrentSpeed -= decelRate * xLastDir * Engine::deltaTime;
        std::cout << "reduce speed" << std::endl;
        if((xCurrentSpeed > 0 && xLastDir < 0) || (xCurrentSpeed < 0 && xLastDir > 0)){
            xCurrentSpeed = 0;
            xDir = 0;
        }else xDir = xLastDir;
    }

    // Input in Y axis
    if(yDir != 0 ){
        yLastDir = yDir;

        if(abs(yCurrentSpeed) < player.speed) yCurrentSpeed += accelRate * yDir * Engine::deltaTime;
        if(abs(yCurrentSpeed) > player.speed) yCurrentSpeed = player.speed * yDir;
    }else{
        if(abs(yCurrentSpeed) > 0) yCurrentSpeed -= decelRate * yLastDir * Engine::deltaTime;
        if((yCurrentSpeed > 0 && yLastDir < 0) || (yCurrentSpeed < 0 && yLastDir > 0)){
            yCurrentSpeed = 0;
            yDir = 0;
        }else yDir = yLastDir;
    }
    std::cout << xCurrentSpeed << " " << xDir << std::endl;
    player.object->Transform(player.object->transform.x + (xCurrentSpeed * Engine::deltaTime), 
                             player.object->transform.y + (yCurrentSpeed * Engine::deltaTime));
}
