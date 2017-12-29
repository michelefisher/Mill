#include <GL/glew.h>
#include <iostream>
#include "Window.h"

Window::Window(int width, int height, const std::string& windowName) : _isFirstMouseMove(true), lastX(width/2), lastY(height/2)
{
    window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLFW window");
    }
}

Window::~Window() {
    glfwDestroyWindow(window);
}

GLFWwindow* Window::getGLFWWindow() const {
    return window;
}

bool Window::isFirstMouseMove() const {
    return _isFirstMouseMove;
}

void Window::setIsFirstMouseMove(bool _isFirstMouseMove) {
    Window::_isFirstMouseMove = _isFirstMouseMove;
}

float Window::getLastX() const {
    return lastX;
}

void Window::setLastX(float lastX) {
    this->lastX = lastX;
}

float Window::getLastY() const {
    return lastY;
}

void Window::setLastY(float lastY) {
    this->lastY = lastY;
}


