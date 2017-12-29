#pragma once

#include <glm/vec3.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/glm.hpp>
#include "CameraMovement.h"

class Camera {
public:
    Camera(float, float, glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f),
           glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f));

    glm::mat4 getViewMatrix();
    void processKeyboardInput(CameraMovement, float);
    void processMouseInput(float, float);
    glm::mat4 &getProjectionMatrix();

    float INIT_YAW = -90.0f;
    float INIT_PITCH = 0.0f;
    float INIT_SPEED = 2.5f;
    float INIT_MOUSE_SENSITIVITY = 0.1f;
private:
    void updateCameraVectors();

    glm::mat4 projectionMatrix;
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 worldUp;
    glm::vec3 right;
    float yaw = INIT_YAW;
    float pitch = INIT_PITCH;
    float speed = INIT_SPEED;
    float mouseSensitivity = INIT_MOUSE_SENSITIVITY;
    constexpr static const float PITCH_LIMIT = 89.0f;
};