#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader(const std::string &vertexPath, const std::string &fragmentPath);

    ~Shader();

    void use() const;

    void setMat4(const std::string &name, const glm::mat4 &matrix) const;
    void setVec4(const std::string& name, const glm::vec4& value) const;

    void setModel(const glm::mat4 &matrix) const;
    void setView(const glm::mat4 &matrix) const;
    void setProj(const glm::mat4 &matrix) const;
    void setColor(const glm::vec4& value) const;

    unsigned int getId() const;

private:
    unsigned int shaderProgramId;

    std::string readFile(const std::string &filePath);

    unsigned int compileShader(unsigned int shaderType, const std::string &shaderSource);
};