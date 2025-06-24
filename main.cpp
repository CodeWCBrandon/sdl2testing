#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <stdlib.h>

bool Init();
void Start();
bool Update();
void PlayerMovement(std::string& processes);
void RenderRectWithColor(SDL_Renderer*& renderer, SDL_Rect& rect, int r, int g, int b, int a);
int Exit(int exitCode);
std::string Input();


// ========= RENDERING ==========
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* background = nullptr;
SDL_Rect windowLayout;

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
    
}

//Updating every frames
bool Update()
{
    SDL_RenderCopy(renderer, background, NULL, &windowLayout); // render image

    RenderRectWithColor(renderer, player, 0, 255, 255, 255);

    //get input
    std::string processes = Input();
    PlayerMovement(processes);

    //processes
    if(processes == "exit") return false;
    return true; // keep looping
}

void PlayerMovement(std::string& processes)
{
    if(processes == "w") player.y -= 5;
    else if(processes == "a") player.x -= 5;
    else if(processes == "s") player.y += 5;
    else if(processes == "d") player.x += 5;
}

void RenderRectWithColor(SDL_Renderer*& renderer, SDL_Rect& rect, int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a); // change renderer color
    SDL_RenderFillRect(renderer, &rect); // render
}

std::string Input()
{
    SDL_Event event;

    //On event trigger
    while(SDL_PollEvent(&event) != 0)
    {
        switch(event.type)
        {
            case SDL_QUIT:
                return "exit";
                break;

            case SDL_KEYDOWN:
                //on key down (keyboard input)
                switch(event.key.keysym.sym)
                {
                    //on click w
                    case SDLK_w:
                        return "w";
                    case SDLK_s:
                        return "s";
                    case SDLK_a:
                        return "a";
                    case SDLK_d:
                        return "d";
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                //on mouse button down
                switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        std::cout << "Clicked left mouse\n";
                        return "left-mouse";
                }
                break;
        }
    }

    return "";
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
