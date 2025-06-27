#include "menu.h"
#include "../engine.h"

Menu::Menu(const std::vector<std::string>& items, int x, int yStart, int spacing, int fontSize) 
{
    for (size_t i = 0; i < items.size(); ++i) 
    {
        Text* text = new Text(items[i], x, yStart + i * spacing, 300, 40, 1); 
        text->SetFont("assets/fonts/ARCADE_N.TTF", fontSize);
        text->SetColor(255, 255, 255, 255); 
        text->SetTexture();
        options.push_back(text);
        labels.push_back(items[i]);
    }
}

Menu::~Menu() 
{
    for (Text* t : options) 
    {
        delete t;
    }
}

void Menu::HandleInput(SDL_Keycode key) 
{
    if (key == SDLK_UP) 
    {
        selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
    } 
    else if (key == SDLK_DOWN) 
    {
        selectedIndex = (selectedIndex + 1) % options.size();
    } 
    else if (key == SDLK_RETURN) 
    {
        done = true;
    }
}

void Menu::Render() 
{
    Engine::renderBuffer.clear();

    for (int i = 0; i < options.size(); ++i) 
    {
        if (i == selectedIndex) 
        {
            options[i]->SetColor(255, 255, 0, 255);   // highlight
        } 
        else 
        {
            options[i]->SetColor(255, 255, 255, 255); // normal
        }
        options[i]->SetTexture();                    
        Engine::AddToRenderBuffer(options[i]);       
    }

    // now let the engine draw them all
    Engine::RenderTexture();
}

bool Menu::IsDone() const 
{
    return done;
}

int Menu::GetSelectedIndex() const 
{
    return selectedIndex;
}

std::string Menu::GetSelectedText() const 
{
    return labels[selectedIndex];
}

void Menu::Reset() 
{
    done = false;
    selectedIndex = 0;
}
