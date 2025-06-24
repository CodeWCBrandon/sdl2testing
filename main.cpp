#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>

int main() 
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "failed to initializing the SDL\n" << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("main", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

    if(!window)
    {
        std::cout << "failed to show the window\n" << SDL_GetError() << std::endl; 
        return 1;
    }

    SDL_Surface* winSurface = SDL_GetWindowSurface(window);

    SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface->format, 128, 128,128));
    
    SDL_UpdateWindowSurface(window);    

    SDL_Delay(5000);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
