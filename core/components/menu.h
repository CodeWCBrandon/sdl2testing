#pragma once

#include "text.h"
#include <vector>
#include <string>

class Menu 
{
    public:
        Menu(const std::vector<std::string>& items, int x = 100, int yStart = 200, int spacing = 40, int fontSize = 24);
        ~Menu();

        void HandleInput(SDL_Keycode key);
        void Render();

        bool IsDone() const;
        int GetSelectedIndex() const;
        std::string GetSelectedText() const;

        void Reset();

    private:
        std::vector<Text*> options;
        std::vector<std::string> labels;
        int selectedIndex = 0;
        bool done = false;
};
