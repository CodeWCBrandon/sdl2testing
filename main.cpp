#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>

void Update();
void Start();
bool Init();
int Exit(int exitCode);


SDL_Window* window;
SDL_Surface* winSurface;

// all technical setup
int main() 
{
    if(!Init())
    {
        std::cout << "failed to intiliazing the SDL\n" << SDL_GetError() << std::endl;
        return Exit(1);
    }
    
    Start();

    while(true)
    {
        Update();

        //updating window
        SDL_UpdateWindowSurface(window);    
    }
    
    return Exit(0);
}

//Game logic
void Start()
{

}

//Updating every frames
void Update()
{
    // Window background rectangle with colors
    SDL_Surface* temp1 = SDL_LoadBMP("testing.gif");
    if(!temp1) std::cout << "Loading img error\n" << SDL_GetError() << std::endl;

    SDL_Surface* img1 = SDL_ConvertSurface(temp1, winSurface->format, 0);
}
    
bool Init()
{
    //Check is SDL Initialized without an error
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "failed to initializing the SDL\n" << SDL_GetError() << std::endl;
        return false;
    }

    //Creating the window
    window = SDL_CreateWindow("main", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

    //Checking the window 
    if(!window)
    {
        std::cout << "failed to show the window\n" << SDL_GetError() << std::endl; 
        return false;
    }

    //Creating the window surface
    winSurface = SDL_GetWindowSurface(window);
}

int Exit(int exitCode)
{
    //Quitting
    SDL_DestroyWindow(window);
    SDL_Quit();
    return exitCode;
}
