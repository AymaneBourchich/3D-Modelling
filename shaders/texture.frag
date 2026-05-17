#version 330 core

in vec2 fragmentTexCoord;
in vec4 fragmentColor;

out vec4 finalColor;

uniform sampler2D texture0;

void main()
{
    vec4 textureColor = texture(texture0, fragmentTexCoord);

    finalColor = textureColor * fragmentColor;
}