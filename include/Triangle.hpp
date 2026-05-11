#pragma once

class Triangle
{
public:
    Triangle();

    ~Triangle();

    void draw() const;

private:
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
};