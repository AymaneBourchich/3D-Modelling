CXX := g++

CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic -Iinclude

TARGET := app

SRC := \
	src/main.cpp \
	src/Shader.cpp \
	src/Camera.cpp \
	src/CubeMap.cpp \
	src/Mesh.cpp \
	src/Model.cpp \
	src/Texture.cpp

LIBS := -lglfw -lGLEW -lGL -lfmt -lassimp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)