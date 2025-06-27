#include "core/engine.h"


// main runner
int main(int argc, char* argv[]) 
{
    if(!Engine::Init())
    {
        std::cout << "failed to intiliazing the SDL\n" << SDL_GetError() << std::endl;
        return Engine::Exit(1);
    }
    
    Engine::Start();

    const double targetFPS = 144;
    const double targetFrameTime = (targetFPS > 0) ? (1000.0 / targetFPS) : 0;

    Uint64 lastFpsTime = SDL_GetPerformanceCounter();
    Uint64 frameCount = 0;

    while (Engine::Update())
    {
        Uint64 frameStart = SDL_GetPerformanceCounter();

        // === loop ===
        Engine::RenderTexture();
        Engine::Input();
        SDL_RenderPresent(Engine::renderer);
        SDL_RenderClear(Engine::renderer);
        // ==================

        Uint64 frameEnd = SDL_GetPerformanceCounter();
        double frameTimeMs = (frameEnd - frameStart) * 1000.0 / SDL_GetPerformanceFrequency();

        // FPS cap
        if (frameTimeMs < targetFrameTime) SDL_Delay(Uint64(targetFrameTime - frameTimeMs));
        

        // === Debug log ===
        frameCount++;
        Uint64 now = SDL_GetPerformanceCounter();
        double elapsedSec = (now - lastFpsTime) / double(SDL_GetPerformanceFrequency());

        if (elapsedSec >= 1.0)
        {
            double fps = frameCount / elapsedSec;
            std::cout << "FPS: " << std::fixed << std::setprecision(2) << fps << "\n";
            
            frameCount = 0;
            lastFpsTime = now;
        }
    }
    
    return Engine::Exit(0);
}