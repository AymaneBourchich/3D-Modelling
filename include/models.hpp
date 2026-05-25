#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

void translate(glm::mat4 &model, glm::vec3 value)
{
    model = glm::translate(model, value);
}

void rotate(glm::mat4 &model, float angle, glm::vec3 axis)
{
    model = glm::rotate(model, angle, axis);
}

void rotateAroundPivot(glm::mat4 &model, float angle, glm::vec3 axis, glm::vec3 pivot)
{
    translate(model, pivot);
    rotate(model, angle, axis);
    translate(model, -pivot);
}

void scale(glm::mat4 &model, glm::vec3 value)
{
    model = glm::scale(model, value);
}




