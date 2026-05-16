CXX := g++

CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic -Iinclude

TARGET := app

SRC := \
	src/main.cpp \
	src/Shader.cpp \
	src/Camera.cpp \
	src/Shape.cpp

LIBS := -lglfw -lGLEW -lGL

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)