#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader(
        const std::string &vertexPath,
        const std::string &fragmentPath);

    ~Shader();

    void use() const;

    void setMat4(
        const std::string &name,
        const glm::mat4 &matrix) const;

    unsigned int getId() const;

private:
    unsigned int shaderProgramId;

    std::string readFile(
        const std::string &filePath);

    unsigned int compileShader(
        unsigned int shaderType,
        const std::string &shaderSource);
};