#pragma once

#include <string>
#include <glm/glm.hpp>
#include "Light.hpp"

class Shader
{
public:
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    Shader();

    ~Shader();

    void use() const;

    void setMat4(const std::string &name, const glm::mat4 &matrix) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;

    void setModel(const glm::mat4 &matrix) const;
    void setView(const glm::mat4 &matrix) const;
    void setProj(const glm::mat4 &matrix) const;
    void setColor(const glm::vec4 &value) const;

    void setMVP(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &proj) const;

    void setMaterial(const Material material) const;
    void setDirLight(const DirLight dirLight) const;
    void setPointLight(const PointLight pointLight) const;
    void setSpotLight(const SpotLight spotLight, const int index) const;

    // void setDiffuseMap(const Texture &texture) const;
    // void setSpecularMap(const Texture &texture) const;

    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

    unsigned int getId() const;
    unsigned int shaderProgramId;

private:
    

    std::string readFile(const std::string &filePath);

    unsigned int compileShader(unsigned int shaderType, const std::string &shaderSource);
};