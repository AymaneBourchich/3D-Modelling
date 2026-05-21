#version 330 core

in vec4 fragmentColor;

uniform vec4 color;

out vec4 finalColor;

void main()
{
    finalColor = color;
}