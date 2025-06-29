# Engine

## Variables

```cpp
static double deltaTime;
```

- Engine::deltaTime == to get the time difference between each frame

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

# Main

This file is for running the code structure, this is the simple layout of **main.cpp**:

```cpp
#include "core/engine.h"

// main runner
int main() 
{
    //initializing
    if(!Engine::Init())
    {
        std::cout << "failed to intiliazing the SDL\n" << SDL_GetError() << std::endl;
        return Engine::Exit(1);
    }
    
    //calling the start function that are overriden in game.cpp
    Engine::Start();

    //keep updating when true
    while (Engine::Update())
    {
        //anything that need to be updated each frame 

        //P.S Do not put game logic here.
    }
    
    //Exiting
    return Engine::Exit(0);
}
```

# Game

This file contains the logic for our game, this is the simple layout of **game.cpp**:

```cpp
#include "core/engine.h"
#include "core/components/object.h"
#include "core/components/vector2d.h"
#include "core/components/text.h"


void Engine::Start()
{
    //put the game logic that you want to run once on start here 
}

//Updating every frames
bool Engine::Update()
{
    //put the game logic that needed each frame here
}
```

# Components

## Entity 

this is an abstract class that works as a parent for classes like: **Object, Text, etc** (more to be added).

### Variables
*the variables here is pretty self explanatory (please understand smh my head)*

```cpp
SDL_Texture* texture; // texture of its entity
SDL_Rect rectFormat; // rect format or (position, size) format for SDL
Vector2d position; // position in 2d plane
double width; // width
double height; // height
int layerMask; // layer or z-index for order of rendering (the less the number the first one to be rendered, ex. background == 0, player == 1. the player will overlap the background because the background is rendered first).
```

### Functions

#### Constuctor
```cpp
Entity(double x, double y, double width, double height, int layerMask);
```

this is used for assigning the value of it's entity on creating the object.

---
#### Transform(double xPos, double yPos)
```cpp
virtual void Transform(double xPos, double yPos);
```

this function is used for assigning the position of a class that inherits **Entity**. Example scenario:

```cpp
Object* player;

//this changes the player's x position and y position
player->Transform(10, 10);
```

---
#### Scale(double width, double height)
```cpp
virtual void Scale(double width, double height);
```

this function is used for assigning the size of a class that inherits **Entity**. Example Scenario:

```cpp
Object* player;

//this changes the player's width and height
player->Scale(10, 10);
```

---
#### SetLayerMask(int layerMask)
```cpp
virtual void SetLayerMask(int layerMask);
```

this function is used for assigning the layerMask of a class that inherits **Entity**. Exmaple Scenario:

```cpp
Object* player;

//this changes the player's layermask
player->SetLayerMask(1);
```

---
#### UpdateRectFormat()
```cpp
virtual void UpdateRectFormat();
```

this function is used for updating the rect format, usually this function **called after changing the some variables value of the Entity (ex. position, width, height)**

---
#### AddToRenderBuffer()
```cpp
virtual void AddToRenderBuffer();
```

this function is used for adding it's object to **render buffer**. example scenario:

```cpp
Object* player

//this adds the player to Engine::renderBuffer
player->AddToRenderBuffer();
```

## Object

this class inherits with **Entity**

### Variables

this class have no variables for now

### Functions

#### Constructor

- Default constructor: for creating an object without a value
- constructor: for creating an object with a value

```cpp
Object(const char* texturePath, double xPos, double yPos, double width, double height, int layerMask);
```

For the constructor we pass every value needed for **Entity** and texturePath for loading a **BMP files (images)**.

---
#### SetTexture()

```cpp
void SetTexture(const char* texturePath);
```

this function is used for assigning **BMP Files(images)** for the object texture. example scenario:

```cpp
Object* player;

player->SetTexture("assets/player.bmp");
```

## Text
This class inherits **Entity**

use example:
```cpp
//calling the constructor to assigning the value
Text* score = new Text("Score: " + std::to_string(currentScore), 25, 25, 100, 12, 1);

//setting up the font
score->SetFont("assets/fonts/ARCADE_N.TTF", 20);

//setting up the colot
score->SetColor(255, 255, 255, 255);

//changing the text
score->SetText("Hello world\n");
```

### Variables
This is the variables for **Text**
```cpp
TTF_Font* font; // font style and size
std::string text; // text to be rendered

//color
int red;
int green;
int blue;
int alpha;
```

### Functions

#### Constructor

to assign the value upon creating an object

```cpp
Text(); // default constructor
Text(std::string text, double xPos, double yPos, double width, double height, int layerMask); // constructor
```

---
#### SetFont()

```cpp
void SetFont(const char* fontPath, int fontSize);
```

To set the font, we need to pass the path (ex. "fonts/arial.ttf")

---
#### SetText()

```cpp
void SetText(std::string text);
```

this function used for changing the text

---
#### SetColor()

```cpp
void SetColor(int red, int green, int blue, int alpha);
```

this function used for changing the color of it's text

---
#### SetTexture()

```cpp
void SetTexture();
```

this function used for updating the values that are changed. usually you don't need to **set texture** manually. because it's **automatically on SetFont(), SetText(), SetColor(), etc**.

## Vector
this class is used for storing the position of an **Entity** in 2D plane

### Variables
2D plane position:

```cpp
double x; //x position
double y; //y position
```

### Functions

#### Constructor

```cpp
Vector2d(double x, double y);
```

this constructor is used for assigning the object on initialization

---
#### Vector2d::Normalize()

```cpp
static void Normalize(double& x, double& y);
```

this function is used for normalizing a movement of an **Entity** 