#include "engine.h"
#include "components/object.h"
#include "components/entity.h"
#include "components/vector2d.h"
#include "components/text.h"

// ========= RENDERING ==========
SDL_Window* Engine::window = nullptr;
SDL_Renderer* Engine::renderer = nullptr;
SDL_Rect Engine::windowLayout;

// ========= INPUTS ===========
std::set<SDL_Keycode> Engine::inputBuffer;
std::vector<Entity*> Engine::renderBuffer;

bool Engine::Init()
{
    // ======= DISPLAY SIZE =========
    int width = 840;
    int height = 600;

    //Check is SDL Initialized without an error
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "failed to initializing the SDL\n" << SDL_GetError() << std::endl;
        return false;
    }

    //Creating the window
    int result = SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);

    //Checking the window 
    if(result != 0)
    {
        std::cout << "failed to show the window\n" << SDL_GetError() << std::endl; 
        return false;
    }

    //window layout for future use
    windowLayout.x = 0;
    windowLayout.y = 0;
    windowLayout.w = width;
    windowLayout.h = height;

    //initialize text
    if(TTF_Init() < 0)
    {
        std::cout << "Error Initializing TTF" << SDL_GetError() << std::endl;
    }

    return true;
}

void Engine::RenderRect(SDL_Renderer*& renderer, SDL_Rect& rect, int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a); // change renderer color
    SDL_RenderFillRect(renderer, &rect); // render
}

void Engine::AddToRenderBuffer(Entity* obj)
{
    Engine::renderBuffer.push_back(obj);

    //sort based on the layermask
    std::sort(Engine::renderBuffer.begin(), Engine::renderBuffer.end(), [](const Entity* a, const Entity* b){
        return a->layerMask < b->layerMask;
    });
}

SDL_Texture* Engine::LoadTexture(SDL_Surface*& surface)
{
    if(!surface)
    {
        std::cout << "Texture failed to load: \n" << SDL_GetError();
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::renderer, surface);

    if(!texture)
    {
        std::cout << "Texture failed to load \n" << SDL_GetError();
        return nullptr;
    }
    SDL_FreeSurface(surface);

    return texture;
}

void Engine::RenderTexture()
{
    for(auto obj : Engine::renderBuffer)
    {
        SDL_RenderCopy(Engine::renderer, obj->texture, NULL, &obj->rectFormat);
    }
}

void Engine::Input()
{
    SDL_Event event;

    //On event trigger
    while(SDL_PollEvent(&event) != 0)
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
                //keyboard down
                inputBuffer.insert(event.key.keysym.sym);
                break;
            
            case SDL_KEYUP:
                //keyboard up
                inputBuffer.erase(event.key.keysym.sym);
                break;
        }
    }
}


int Engine::Exit(int exitCode)
{
    //Quitting
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return exitCode;
}
