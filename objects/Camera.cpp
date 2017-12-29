#include <cmath>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Camera.h"

Camera::Camera(float width, float height, glm::vec3 pos, glm::vec3 worldUp, glm::vec3 front) :
        pos(pos),
        worldUp(worldUp),
        front(front),
        projectionMatrix(glm::perspective(glm::radians(45.0f), width/height, 0.1f, 100.0f)) {
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(pos, pos + front, up);
}

void Camera::processKeyboardInput(CameraMovement cameraMovement, float deltaTime) {
    float velocity = speed * deltaTime;

    switch (cameraMovement) {
        case CameraMovement::FORWARD:
            pos += front * velocity;
            break;
        case CameraMovement::BACKWARD:
            pos -= front * velocity;
            break;
        case CameraMovement::LEFT:
            pos -= right * velocity;
            break;
        case CameraMovement::RIGHT:
            pos += right * velocity;
    }
}

void Camera::processMouseInput(float xOffset, float yOffset) {
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > PITCH_LIMIT) {
        pitch = PITCH_LIMIT;
    }
    if (pitch < (-1 * PITCH_LIMIT)) {
        pitch = -1 * PITCH_LIMIT;
    }

    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

glm::mat4 &Camera::getProjectionMatrix() {
    return projectionMatrix;
}
