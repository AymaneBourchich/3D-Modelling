#include "Camera.hpp"





extern GLFWwindow *globalWindow;

Camera::Camera()
{
    position = glm::vec3(0.0f, 0.5f, 3.0f);

    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    front = glm::vec3(0.0f, -0.5f, -1.0f);

    yaw = -90.0f;

    pitch = 0.0f;

    movementSpeed = 3.0f;

    mouseSensitivity = 0.01f;

    firstMouse = true;

    lastMouseX = 640.0f;
    lastMouseY = 360.0f;

    updateCameraVectors();
}

void Camera::processKeyboardInput(
    float deltaTime)
{
    float velocity = movementSpeed * deltaTime;

    if (glfwGetKey(globalWindow, GLFW_KEY_W) == GLFW_PRESS)
    {
        position += front * velocity;
    }

    if (glfwGetKey(globalWindow, GLFW_KEY_S) == GLFW_PRESS)
    {
        position -= front * velocity;
    }

    if (glfwGetKey(globalWindow, GLFW_KEY_A) == GLFW_PRESS)
    {
        position -= right * velocity;
    }

    if (glfwGetKey(globalWindow, GLFW_KEY_D) == GLFW_PRESS)
    {
        position += right * velocity;
    }

    if (glfwGetKey(globalWindow, GLFW_KEY_UP) == GLFW_PRESS)
    {
        position += worldUp * velocity;
    }

    if (glfwGetKey(globalWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        position -= worldUp * velocity;
    }
}

void Camera::processMouseInput(
    double mouseX,
    double mouseY)
{
    if (firstMouse)
    {
        lastMouseX = static_cast<float>(mouseX);
        lastMouseY = static_cast<float>(mouseY);
        firstMouse = false;
    }

    float xOffset = static_cast<float>(mouseX) - lastMouseX;

    float yOffset = lastMouseY - static_cast<float>(mouseY);

    lastMouseX = static_cast<float>(mouseX);

    lastMouseY = static_cast<float>(mouseY);

    xOffset *= mouseSensitivity;

    yOffset *= mouseSensitivity;

    yaw += xOffset;

    pitch += yOffset;

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }

    if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    glm::vec3 direction;

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(direction);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, position + front, up);
}