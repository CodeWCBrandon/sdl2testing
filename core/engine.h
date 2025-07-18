#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <set>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <chrono>

class Object; // forward declaration
class Entity;
class Text;

struct Mouse
{
    int x;
    int y;
};

class Engine
{
    public:
        static SDL_Rect windowLayout;
        static SDL_Window* window;
        static SDL_Renderer* renderer;
        static std::set<SDL_Keycode> inputBuffer;
        static std::vector<Entity*> renderBuffer;
        static double deltaTime;
        static Mouse mousePos;

        //normal state
        static bool Init();
        static void Start();
        static void Update();
        static int Exit(int exitCode);

        //input handling
        static void Input();

        //handle rendering
        static void RenderRect(SDL_Renderer*& renderer, SDL_Rect& rect, int r, int g, int b, int a);
        static void RenderTexture();
        static void AddToRenderBuffer(Entity* obj);
        static SDL_Texture* LoadTexture(SDL_Surface*& surface);
};