#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <GL/glew.h>
#include "Callbacks.h"
#include "Application.h"


Application::Application(unsigned width, unsigned height, const std::string& applicationName) :
        timer(),
        camera((float)width, (float)height, glm::vec3(0.0f, 1.0f, 5.0f)),
        WINDOW_WIDTH(width),
        WINDOW_HEIGHT(height),
        APPLICATION_NAME(applicationName),
        objectsToDraw()
{
    initGLFW();
    window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, APPLICATION_NAME);
    glfwMakeContextCurrent(window->getGLFWWindow());
    initGLEW();

    Callbacks::setIsFirstMouseMove(true);
    Callbacks::setLastY(height/2);
    Callbacks::setLastX(width/2);
    Callbacks::setCamera(&camera);

    glfwMakeContextCurrent(window->getGLFWWindow());
    glfwSetFramebufferSizeCallback(window->getGLFWWindow(), Callbacks::frameBufferSizeCallback);
    glfwSetCursorPosCallback(window->getGLFWWindow(), Callbacks::mouseCallback);

    glfwSetWindowUserPointer(window->getGLFWWindow(), this);
    glfwSetInputMode(window->getGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);
}

void Application::initGLFW() {
    glfwSetErrorCallback(Callbacks::errorCallback);
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void Application::initGLEW() {
    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK) {
        auto* errorString = reinterpret_cast<const char*>(glewGetErrorString(glewStatus));
        std::string errorDescription = std::string(errorString);

        throw std::runtime_error("GLEW initialization error: " + errorDescription);
    }
}

void Application::run() {
    GLenum error;

    while(!glfwWindowShouldClose(window->getGLFWWindow())) {
        if ((error = glGetError()) != GL_NO_ERROR) {
            glfwTerminate();
            throw std::runtime_error("Render loop has detected error");
        }

        timer.updateDeltaTime();

        processInput(window->getGLFWWindow());

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(BasicObject* object: objectsToDraw) {
            object->draw(camera.getViewMatrix(), camera.getProjectionMatrix());
        }

        skybox->draw(camera.getViewMatrix(), camera.getProjectionMatrix());

        glfwSwapBuffers(window->getGLFWWindow());
        glfwPollEvents();
    }

    glfwTerminate();
}

void Application::addObjectToScene(BasicObject* basicObject) {
    objectsToDraw.push_back(basicObject);
}

void Application::addObjectToScene(Skybox* skybox) {
    this->skybox = skybox;
}

void Application::processInput(GLFWwindow* glfwWindow) {
    if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(glfwWindow, true);

    if (glfwGetKey(glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboardInput(CameraMovement::FORWARD, timer.getDeltaTime());
    if (glfwGetKey(glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboardInput(CameraMovement::BACKWARD, timer.getDeltaTime());
    if (glfwGetKey(glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboardInput(CameraMovement::LEFT, timer.getDeltaTime());
    if (glfwGetKey(glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboardInput(CameraMovement::RIGHT, timer.getDeltaTime());
}

Camera& Application::getCamera() {
    return camera;
}