#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <set>
#include <stdlib.h>

bool Init();
void Start();
bool Update();
void PlayerMovement();
void RenderRectWithColor(SDL_Renderer*& renderer, SDL_Rect& rect, int r, int g, int b, int a);
int Exit(int exitCode);
void Input();


// ========= RENDERING ==========
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* background = nullptr;
SDL_Rect windowLayout;

// ========= INPUTS ===========
std::set<SDL_Keycode> inputBuffer;

// ========= VARIABLES ==========
SDL_Rect player = {50, 50, 20, 20};

// all technical setup
int main() 
{
    if(!Init())
    {
        std::cout << "failed to intiliazing the SDL\n" << SDL_GetError() << std::endl;
        return Exit(1);
    }
    
    Start();

    while(Update())
    {
        SDL_RenderPresent(renderer); // updating window
        SDL_Delay(10); // delay per update
        SDL_RenderClear(renderer); // clearing after rendering
    }
    
    return Exit(0);
}

//Game logic
void Start()
{
    //adding backgrounds
    SDL_Surface* tempBG = SDL_LoadBMP("spacebg.bmp");
    background = SDL_CreateTextureFromSurface(renderer, tempBG);
    SDL_FreeSurface(tempBG); // flushing temp Background    

    //centering player
    player.x = (windowLayout.w - player.w) / 2;
    player.y = (windowLayout.h - player.h) / 2;
}

//Updating every frames
bool Update()
{
    SDL_RenderCopy(renderer, background, NULL, &windowLayout); // render image

    RenderRectWithColor(renderer, player, 0, 255, 255, 255);

    Input();
    PlayerMovement();

    //processes
    if(inputBuffer.count(SDLK_ESCAPE)) return false;
    return true; // keep looping
}

void PlayerMovement()
{
    if(inputBuffer.count(SDLK_w)) player.y -= 5;
    if(inputBuffer.count(SDLK_a)) player.x -= 5;
    if(inputBuffer.count(SDLK_s)) player.y += 5;
    if(inputBuffer.count(SDLK_d)) player.x += 5;
}

void RenderRectWithColor(SDL_Renderer*& renderer, SDL_Rect& rect, int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a); // change renderer color
    SDL_RenderFillRect(renderer, &rect); // render
}

void Input()
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

bool Init()
{
    // ======= SETTINGS =========
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

int Exit(int exitCode)
{
    //Quitting
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return exitCode;
}
