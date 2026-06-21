#include "Shader.hpp"

#include <GL/glew.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <glm/gtc/type_ptr.hpp>
#include <fmt/core.h>

Shader::Shader(
    const std::string &vertexPath,
    const std::string &fragmentPath)
{
    std::string vertexSource = readFile(vertexPath);
    std::string fragmentSource = readFile(fragmentPath);

    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);

    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    shaderProgramId = glCreateProgram();

    glAttachShader(shaderProgramId, vertexShader);
    glAttachShader(shaderProgramId, fragmentShader);

    glLinkProgram(shaderProgramId);

    int success;

    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);

    if (!success)
    {
        char infoLog[512];

        glGetProgramInfoLog(
            shaderProgramId,
            512,
            nullptr,
            infoLog);

        std::cerr << "Shader linking failed:\n"
                  << infoLog << '\n';
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::Shader()
{
    Shader("shaders/basic.vert", "shaders/basic.frag");
}

Shader::~Shader()
{
    glDeleteProgram(shaderProgramId);
}

void Shader::use() const
{
    glUseProgram(shaderProgramId);
}

unsigned int Shader::getId() const
{
    return shaderProgramId;
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(shaderProgramId, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(shaderProgramId, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setMat4(const std::string &name, const glm::mat4 &matrix) const
{
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramId, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setModel(const glm::mat4 &matrix) const
{
    setMat4("model", matrix);
}
void Shader::setView(const glm::mat4 &matrix) const
{
    setMat4("view", matrix);
}
void Shader::setProj(const glm::mat4 &matrix) const
{
    setMat4("projection", matrix);
}
void Shader::setColor(const glm::vec4 &value) const
{
    setVec4("color", value);
}
void Shader::setMVP(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &proj) const
{
    setModel(model);
    setView(view);
    setProj(proj);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(shaderProgramId, name.c_str()), value);
}

void Shader::setMaterial(const Material material) const
{
    setVec3("material.ambient", material.ambient);
    setVec3("material.diffuse", material.diffuse);
    setVec3("material.specular", material.specular);
    setFloat("material.shininess", material.shininess);
}

void Shader::setDirLight(const DirLight dirLight) const
{
    setVec3("dirLight.direction", dirLight.direction);
    setVec3("dirLight.ambient", dirLight.ambient);
    setVec3("dirLight.diffuse", dirLight.diffuse);
    setVec3("dirLight.specular", dirLight.specular);
}

void Shader::setPointLight(const PointLight pointLight) const
{
    setVec3("pointLight.position", pointLight.position);

    setVec3("pointLight.ambient", pointLight.ambient);
    setVec3("pointLight.diffuse", pointLight.diffuse);
    setVec3("pointLight.specular", pointLight.specular);

    setFloat("pointLight.constant", pointLight.constant);
    setFloat("pointLight.linear", pointLight.linear);
    setFloat("pointLight.quadratic", pointLight.quadratic);
}

void Shader::setSpotLight(const SpotLight spotLight, const int index) const
{

    setVec3(fmt::format("spotLight[{}].position", index), spotLight.position);
    setVec3(fmt::format("spotLight[{}].direction", index), spotLight.direction);

    setFloat(fmt::format("spotLight[{}].cutOff", index), spotLight.cutOff);
    setFloat(fmt::format("spotLight[{}].outerCutOff", index), spotLight.outerCutOff);

    setFloat(fmt::format("spotLight[{}].constant", index), spotLight.constant);
    setFloat(fmt::format("spotLight[{}].linear", index), spotLight.linear);
    setFloat(fmt::format("spotLight[{}].quadratic", index), spotLight.quadratic);

    setVec3(fmt::format("spotLight[{}].ambient", index), spotLight.ambient);
    setVec3(fmt::format("spotLight[{}].diffuse", index), spotLight.diffuse);
    setVec3(fmt::format("spotLight[{}].specular", index), spotLight.specular);
}

// void Shader::setDiffuseMap(const Texture &texture) const
// {
//     setInt("material.diffuse", 0);
//     texture.bind(0);
// }

// void Shader::setSpecularMap(const Texture &texture) const
// {
//     setInt("material.specular", 1);
//     texture.bind(1);
// }

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(shaderProgramId, name.c_str()), value);
}

std::string Shader::readFile(const std::string &filePath)
{
    std::ifstream fileStream(filePath);

    if (!fileStream.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    return buffer.str();
}

unsigned int Shader::compileShader(unsigned int shaderType, const std::string &shaderSource)
{
    unsigned int shader = glCreateShader(shaderType);
    const char *source = shaderSource.c_str();

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char infoLog[512];

        glGetShaderInfoLog(shader, 512, nullptr, infoLog);

        std::cerr << "Shader compilation failed:\n"
                  << infoLog << '\n';
    }

    return shader;
}