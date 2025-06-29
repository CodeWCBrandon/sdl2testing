#include "core/engine.h"
#include "menu.h"

// main runner
int main(int argc, char* argv[]) 
{
    if(!Engine::Init())
    {
        std::cout << "failed to intiliazing the SDL\n" << SDL_GetError() << std::endl;
        return Engine::Exit(1);
    }
    
    if (!Menu::MainMenu()) 
    {
        return Engine::Exit(0);  
    }

    Engine::Start();              
    
    const double targetFPS = 60;
    const double targetFrameTime = (targetFPS > 0) ? (1000.0 / targetFPS) : 0;
    
    Uint64 lastFpsTime = SDL_GetPerformanceCounter();
    Uint64 frameCount = 0;

    Uint64 prevTime = SDL_GetPerformanceCounter(); // prev time for delta time
    
    while(true)
    {
        // === deltaTime ===
        Uint64 currTime = SDL_GetPerformanceCounter();
        Engine::deltaTime = (currTime - prevTime) / (double)SDL_GetPerformanceFrequency();
        prevTime = currTime;
        // std::cout << Engine::deltaTime << "\n";
        // =================
        

        Uint64 frameStart = SDL_GetPerformanceCounter();

        // === loop ===
        Engine::Update();
        Engine::RenderTexture();
        Engine::Input();
        SDL_RenderPresent(Engine::renderer);
        SDL_RenderClear(Engine::renderer);
        // ============
        
        Uint64 frameEnd = SDL_GetPerformanceCounter();
        double frameTimeMs = (frameEnd - frameStart) * 1000.0 / SDL_GetPerformanceFrequency();
        

        //exit from the game
        if(Engine::inputBuffer.count(SDLK_ESCAPE)) break;

        // FPS cap
        if (frameTimeMs < targetFrameTime) SDL_Delay(Uint64(targetFrameTime - frameTimeMs));
        

        // === Debug log ===
        frameCount++;
        Uint64 now = SDL_GetPerformanceCounter();
        double elapsedSec = (now - lastFpsTime) / double(SDL_GetPerformanceFrequency());

        if (elapsedSec >= 1.0)
        {
            system("clear");
            // debug per second
            
            //FPS
            double fps = frameCount / elapsedSec;
            std::cout << "FPS: " << std::fixed << std::setprecision(2) << fps << "\n";
            
            frameCount = 0;
            lastFpsTime = now;

            //Draw Calls
            std::cout << "Draw Calls: " << Engine::renderBuffer.size() << "\n";

        }
    }
    
    return Engine::Exit(0);
}