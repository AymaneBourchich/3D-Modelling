#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    Camera();

    void processKeyboardInput(float deltaTime);

    void processMouseInput(double mouseX, double mouseY);

    glm::mat4 getViewMatrix() const;

private:
    void updateCameraVectors();

private:
    glm::vec3 position;

    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;

    bool firstMouse;

    float lastMouseX;
    float lastMouseY;
};