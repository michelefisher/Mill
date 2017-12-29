#include <string>
#include "Callbacks.h"

bool Callbacks::isFirstMouseMove = true;
float Callbacks::lastX = 0.0f;
float Callbacks::lastY = 0.0f;
Camera* Callbacks::camera = nullptr;

void Callbacks::errorCallback(int errorNumber, const char* errorDescription) {
    glfwTerminate();

    std::string errorMessage = "Error [" + std::to_string(errorNumber) + "]: " + errorDescription;
    throw std::runtime_error(errorMessage);
}

void Callbacks::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (isFirstMouseMove) {
        lastX = xpos;
        lastY = ypos;
        isFirstMouseMove = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera->processMouseInput(xoffset, yoffset);
}

void Callbacks::frameBufferSizeCallback(GLFWwindow* window, int newWidth, int newHeight) {
    glViewport(0, 0, newWidth, newHeight);
}

void Callbacks::setCamera(Camera* camera) {
    Callbacks::camera = camera;
}

void Callbacks::setLastX(float lastX) {
    Callbacks::lastX = lastX;
}

void Callbacks::setLastY(float lastY) {
    Callbacks::lastY = lastY;
}

void Callbacks::setIsFirstMouseMove(bool isFirstMouseMove) {
    Callbacks::isFirstMouseMove = isFirstMouseMove;
}


