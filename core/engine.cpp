#include "engine.h"
#include "components/object.h"

// ========= RENDERING ==========
SDL_Window* Engine::window = nullptr;
SDL_Renderer* Engine::renderer = nullptr;
SDL_Rect Engine::windowLayout;

// ========= INPUTS ===========
std::set<SDL_Keycode> Engine::inputBuffer;

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

    return true;
}

void Engine::RenderRect(SDL_Renderer*& renderer, SDL_Rect& rect, int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a); // change renderer color
    SDL_RenderFillRect(renderer, &rect); // render
}

SDL_Texture* Engine::LoadTexture(SDL_Renderer*& renderer, const char* texturePath)
{
    SDL_Surface* temp = SDL_LoadBMP(texturePath);
    if(!temp)
    {
        std::cout << "Texture failed to load: " << texturePath << "\n" << SDL_GetError();
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp);

    if(!texture)
    {
        std::cout << "Texture failed to load: " << texturePath << "\n" << SDL_GetError();
        return nullptr;
    }

    SDL_FreeSurface(temp);


    return texture;
}

void Engine::RenderTexture(SDL_Renderer*& renderer, SDL_Texture*& texture, Object& obj)
{
    //object to SDL_Rect
    SDL_Rect rect;
    rect.h = obj.height;
    rect.w = obj.width;
    rect.x = obj.pos.xPos;
    rect.y = obj.pos.yPos;

    SDL_RenderCopy(renderer, texture, NULL, &rect);
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
