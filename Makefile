CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf

SRC = $(wildcard core/*.cpp) $(wildcard core/components/*.cpp) main.cpp game.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

setup:
	sudo pacman -S sdl2 sdl2_image sdl2_mixer sdl2_ttf

winbuild:
	x86_64-w64-mingw32-g++ $(SRC) -o game.exe \
	-static-libgcc -static-libstdc++ \
	-I/usr/x86_64-w64-mingw32/include/SDL2 \
	-L/usr/x86_64-w64-mingw32/lib \
	-Dmain=SDL_main \
	-lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

run: $(TARGET) 
	./$(TARGET)

clear:
	rm -f $(OBJ) $(TARGET) game.exe
