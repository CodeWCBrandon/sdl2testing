#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>

void Update();
void Start();
bool Init();
int Exit(int exitCode);


SDL_Window* window;
SDL_Rect windowLayout;
SDL_Surface* winSurface;
SDL_Surface* background = nullptr;

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
        SDL_Delay(5000);
    }
    
    return Exit(0);
}

//Game logic
void Start()
{
    //adding backgrounds
    SDL_Surface* tempBG = SDL_LoadBMP("spacebg.bmp");
    background = SDL_ConvertSurface(tempBG, winSurface->format, 0);
    SDL_FreeSurface(tempBG); // flushing temp Background

}

//Updating every frames
void Update()
{
    SDL_BlitSurface(background, NULL, winSurface, NULL); // render img
    SDL_BlitScaled(background, NULL, winSurface, &windowLayout); //scaling img
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
    window = SDL_CreateWindow("main", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    //Checking the window 
    if(!window)
    {
        std::cout << "failed to show the window\n" << SDL_GetError() << std::endl; 
        return false;
    }

    //Creating the window surface
    winSurface = SDL_GetWindowSurface(window);

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
    SDL_DestroyWindow(window);
    SDL_Quit();
    return exitCode;
}
