#pragma once
#include "components/object.h"
#include "components/vector2d.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <set>
#include <stdlib.h>

class Engine
{
    public:
        static SDL_Rect windowLayout;
        static SDL_Window* window;
        static SDL_Renderer* renderer;
        static std::set<SDL_Keycode> inputBuffer;

        //normal state
        static bool Init();
        static void Start();
        static bool Update();
        static int Exit(int exitCode);

        //input handling
        static void Input();
        static void IsKeyDown(SDL_Keycode key);

        //handle rendering
        static void RenderRect(SDL_Renderer*& renderer, SDL_Rect& rect, int r, int g, int b, int a);
        static void RenderTexture(SDL_Renderer*& renderer, const char* texturePath, Object& obj);

};