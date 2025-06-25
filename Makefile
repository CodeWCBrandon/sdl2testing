CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`

SRC = main.cpp $(wildcard core/*.cpp) $(wildcard core/components/*.cpp) game.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET) 
	./$(TARGET)
	$(MAKE) clear

clear:
	rm -f $(OBJ) $(TARGET)