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

    while(Engine::Update())
    {
        Engine::RenderTexture();
        Engine::Input();
        SDL_RenderPresent(Engine::renderer); // updating window
        SDL_Delay(10); // delay per update
        SDL_RenderClear(Engine::renderer); // clearing after rendering
    }
    
    return Engine::Exit(0);
}