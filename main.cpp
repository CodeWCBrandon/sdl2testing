#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <stdlib.h>

bool Update();
void Start();
bool Init();
int Exit(int exitCode);
std::string Input();


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

    while(Update())
    {
        //updating window
        SDL_UpdateWindowSurface(window);    
        SDL_Delay(10);
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
bool Update()
{
    SDL_BlitSurface(background, NULL, winSurface, NULL); // render img
    SDL_BlitScaled(background, NULL, winSurface, &windowLayout); //scaling img

    //get input
    std::string processes = Input();

    if(processes == "exit")
    {
        return false; // stop looping
    }

    return true; // keep looping
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
                        std::cout << "Clicked W\n";
                        break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                //on mouse button down
                switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        std::cout << "Clicked left mouse\n";
                        break;
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
