#version 330 core

in vec2 fragmentTexCoord;

out vec4 finalColor;

uniform sampler2D texture0;

void main()
{
    vec4 textureColor = texture(texture0, fragmentTexCoord);

    finalColor = textureColor;
}