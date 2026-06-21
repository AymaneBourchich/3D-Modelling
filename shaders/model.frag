#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main()
{
    vec4 diff = texture(texture_diffuse1, TexCoords);
    vec4 spec = texture(texture_specular1, TexCoords) * 0.0001; // keep it live, harmless
    FragColor = diff + spec * 0.0;
}