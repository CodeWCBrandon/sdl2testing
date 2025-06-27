# Engine

## Variables

### Engine::windowLayout
```cpp
static SDL_Rect windowLayout;
```

this variable is used for getting the windowLayout
```cpp
Engine::windowLayout.x; //window location x axis
Engine::windowLayout.y; //window location y axis
Engine::windowLayout.w; //window width
Engine::windowLayout.h; //window height
```

---
### Engine::window
```cpp
static SDL_Window* window;
```

this variable is used for saving the window (as in seperate window for the game). added in **engine.cpp**

---
### Engine::renderer
```cpp
static SDL_Renderer* renderer;
```

this variable is used for the renderer. just use **Engine::renderer** whenever you need to pass your renderer as an argument. Example scenario

```cpp
//passing Engine::renderer when needed
SDL_RenderCopy(Engine::renderer, obj->texture, NULL, &obj->rectFormat);
```

---
### Engine::inputBuffer
```cpp
static std::set<SDL_Keycode> inputBuffer;
```

this variable is used for saving the user input on hold. receiving input from **Engine::Input()**, treat it like **std::set**. use case example of checking the buffer

```cpp
if(Engine::inputBuffer.count(SDLK_a)) std::cout << "user press a";
```

---
### Engine::renderBuffer
```cpp
static std::vector<Entity*> renderBuffer;
```

this variable is used for a storage on what to render. receiving data from **Engine::AddToRenderBuffer(Entity\* obj)**. usually you **don't** need to call the **Engine::AddToRenderBuffer(obj)** manually. because every component that inherits to Entity (Object, Text) have it's own dedicated function to **add to render buffer**

## Functions

### Engine::Init()

Engine::Init() usually used for initialization of SDL etc called in **main.cpp**

---
### Engine::Start()

Engine::Start() is the part of start function *i'm pretty sure it's self explanatory* the function is initialized in **game.cpp** and called in **main.cpp** usually this is used for game logic where as only called **once** after callind Engine::Init()

```cpp
void Engine::Start()
{
    //called once on start
}
```

---
### Engine::Update()

Engine::Update() is the part of update function which initialized in **game.cpp** and called in **main.cpp** this function called **per frame** after calling Engine::Init() and Engine::Start()

```cpp
bool Engine::Update()
{
    //called each frame
}
```

this function return a boolean which **keep update** if the function **return true** and stop updating when the function **return false**

---
### Engine::Exit()

```cpp
static int Engine::Exit(int exitCode);
```

this function is used for freeing memory at the end with an **exitCode** as a marker if the program runs as expected **Engine::Exit(0)** else, pass any number except 0 to Engine::Exit(). this function is initialized in **engine.cpp** and called in **main.cpp**

---
### Engine::Input()

```cpp
static void Input();
```

this function is used for listening to user input and store it in **inputBuffer** (*i mean it's pretty self explanatory*) Initialized in **engine.cpp** and called every frame in **main.cpp**

---
### Engine::RenderRect() 

***Deprecated***
```cpp
//use Engine::AddToRenderBuffer(Entity* obj) instead

static void RenderRect(SDL_Renderer*& renderer, SDL_Rect& rect, int r, int g, int b, int a);
```

this function is used for Render an SDL_Rect

---
### Engine::RenderTexture()

```cpp
static void RenderTexture()
```

this function is used for Rendering every Entity in **renderBuffer**. initialized in **engine.cpp** called each frame in **main.cpp**

---
### Engine::AddToRenderBuffer()

```cpp
static void AddToRenderBuffer(Entity* obj);
```

this function is used for adding Entity to **renderBuffer**. initialized in **engine.cpp** called in a function in **Entity.h** (*you don't really need this, because every entity have it's own function that uses this*)

---
### Engine::LoadTexture()

```cpp
static SDL_Texture* LoadTexture(SDL_Surface*& surface);
```

this function is used for converting automatically from SDL_Surface to SDL_Texture
keep in mind **both type are pointer**.

use case example::
```cpp
//loading text
SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
texture = Engine::LoadTexture(textSurface);

//loading BMP (image)
SDL_Surface* surface = SDL_LoadBMP(texturePath);
texture = Engine::LoadTexture(surface);
```

initialized in **engine.cpp** and used in **components** for converting to textures