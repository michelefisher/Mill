#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

void errorCallback(int errorNumber, const char* errorDescription) {
    glfwTerminate();

    string errorMessage = "Error [" + to_string(errorNumber) + "]: " + errorDescription;
    throw runtime_error(errorMessage);
}

GLFWwindow* createWindow(unsigned int width, unsigned int height, const string &title, bool isFullScreen = false) {
    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        throw runtime_error("Failed to initialize GLFW window");
    }

    return window;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebufferSizeCallback(GLFWwindow* window, int newWidth, int newHeight) {
    glViewport(0, 0, newWidth, newHeight);
}

GLFWwindow* setupWindow() {
    GLenum glewStatus;
    GLFWwindow* window;

    glfwSetErrorCallback(errorCallback);
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = createWindow(800, 600, "OpenGL");
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    glewStatus = glewInit();
    if (glewStatus != GLEW_OK) {
        auto* errorString = (const char*)glewGetErrorString(glewStatus);
        string errorDescription = string(errorString);

        throw runtime_error("GLEW initialization error: " + errorDescription);
    }

    return window;
}

int main() {
    GLFWwindow* window = setupWindow();

    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.5f, 0.2f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}