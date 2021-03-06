#include "../headers/Camera.hpp"

Camera::Camera(glm::vec2 windowSize)
{
    position = glm::vec3(0.0f, 0.0f, 1.0f);
    forward = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);

    SetProjectionMatrix(45.0f, (float) windowSize.x / (float) windowSize.y, 0.1f,100.0f);
}

Camera::Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up, glm::vec3 rotation, glm::vec2 windowSize)
{
    Camera::position = position;
    Camera::forward = forward;
    Camera::up = up;
    Camera::rotation = rotation;

    SetProjectionMatrix(45.0f, (float) windowSize.x / (float) windowSize.y, 0.1f,100.0f);
}

glm::mat4 Camera::GetViewMatrix()
{

    rotation.y = Clamp(rotation.y, 1.0f, -1.0f);
    float camY = rotation.y * zoom;
    float camX = sin(rotation.x) * zoom * cos(rotation.y);
    float camZ = cos(rotation.x) * zoom * cos(rotation.y);

    glm::mat4 view;
    view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

    return view;
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return projection;
}

glm::vec3 Camera::GetCameraPos()
{ return position; }

glm::vec3 Camera::GetCameraForward()
{ return forward; }

glm::vec3 Camera::GetCameraUp()
{ return up; }

glm::vec3 Camera::GetRotation()
{ return rotation; }

float Camera::GetZoom()
{ return zoom; }

void Camera::SetProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane)
{
    Camera::fov = fov;
    Camera::aspectRatio = aspectRatio;
    Camera::nearPlane = nearPlane;
    Camera::farPlane = farPlane;

    Camera::projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane,farPlane);
}

void Camera::SetCameraPos(glm::vec3 position)
{
    Camera::position = position;
}

void Camera::SetCameraForward(glm::vec3 forward)
{
    Camera::forward = forward;
}

void Camera::SetCameraUp(glm::vec3 up)
{
    Camera::up = up;
}

void Camera::SetRotation(glm::vec3 rotation)
{
    Camera::rotation = rotation;
}

void Camera::InputHandler(GLFWwindow *window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        rotation.x += 3 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        rotation.x -= 3 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        rotation.y += 3 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        rotation.y -= 3 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        zoom -= 3 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        zoom += 3 * deltaTime;

    zoom = Clamp(zoom, 20, 2);
}
