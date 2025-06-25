CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`

SRC = main.cpp core/engine.cpp game.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clear:
	rm -f $(OBJ) $(TARGET)