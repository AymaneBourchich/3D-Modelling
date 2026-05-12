#pragma once

class Cube
{
public:
    Cube();

    ~Cube();

    void draw() const;

private:
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
};