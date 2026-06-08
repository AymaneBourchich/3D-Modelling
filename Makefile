CXX := g++

CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic -Iinclude

TARGET := app

SRC := \
	src/main.cpp \
	src/Shader.cpp \
	src/Camera.cpp \
	src/Shape.cpp \
	src/Texture.cpp \
	src/CubeMap.cpp

LIBS := -lglfw -lGLEW -lGL -lfmt

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)