#pragma once
#include <vector>
#include "Vertex.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
class Mesh {
    public:
        // mesh data
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void Draw(Shader &shader);
    private:
        unsigned int VAO, VBO, EBO;

        void setupMesh();
}; 