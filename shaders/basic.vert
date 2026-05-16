#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexCoord;
layout (location = 3) in vec4 vertexColor;

out vec4 fragmentColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    fragmentColor = vertexColor;

    gl_Position =
        projection *
        view *
        model *
        vec4(vertexPosition, 1.0);
}