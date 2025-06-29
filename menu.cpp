#include "menu.h"

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

bool Menu::MainMenu()
{
    std::vector<std::string> items = { "Start Game", 
                                       "Exit      "};
    Menu menu(items, 100, 200, 40, 24);

    menu.Render();

    while (!menu.IsDone()) 
    {
        Engine::Input(); // takes input
        menu.HandleInput(menu); // check the input

        SDL_Delay(50);
    }

    return (menu.GetSelectedIndex() == 0);
}

void Menu::HandleInput(Menu& menu) 
{
    int timeout = 100; // delay between input
    if (Engine::inputBuffer.count(SDLK_UP)) 
    {
        selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
        menu.Render(); // render or changes
        SDL_Delay(timeout);
    }

    if (Engine::inputBuffer.count(SDLK_DOWN)) 
    {
        selectedIndex = (selectedIndex + 1) % options.size();
        menu.Render();
        SDL_Delay(timeout);
    }
    
    if (Engine::inputBuffer.count(SDLK_RETURN)) 
    {
        Engine::renderBuffer.clear();
        menu.done = true;
    }
}

void Menu::Render() 
{
    SDL_SetRenderDrawColor(Engine::renderer, 0, 0, 0, 255);
    SDL_RenderClear(Engine::renderer);

    Engine::renderBuffer.clear();

    for (int i = 0; i < int(options.size()); ++i) 
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

    SDL_RenderPresent(Engine::renderer);
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
