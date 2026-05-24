#include "Shader.hpp"

#include <GL/glew.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <glm/gtc/type_ptr.hpp>

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
    use();
    setModel(model);
    setView(view);
    setProj(proj);
}

void Shader::setInt(const std::string &name, int value) const
{
    use();
    glUniform1i(glGetUniformLocation(shaderProgramId, name.c_str()), value);
}

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