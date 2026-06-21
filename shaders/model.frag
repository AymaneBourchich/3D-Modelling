#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

// This struct MUST match the name "material" used in Mesh::Draw
struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    sampler2D texture_normal1;
    sampler2D texture_height1;
};

uniform Material material;

void main()
{    
    // We sample from the struct member to match the C++ uniform name
    // material.texture_diffuse1 was set by your Mesh::Draw loop
    FragColor = texture(material.texture_diffuse1, TexCoords);
}