#pragma once

#include <string>
#include <GLFW/glfw3.h>
#include "objects/Camera.h"

class Window {
public:
    Window(int, int, const std::string&);
    ~Window();

    GLFWwindow* getGLFWWindow() const;
    bool isFirstMouseMove() const;
    void setIsFirstMouseMove(bool _isFirstMouseMove);
    float getLastX() const;
    void setLastX(float lastX);
    float getLastY() const;
    void setLastY(float lastY);
private:
    GLFWwindow* window;

    /* data for mouseCallback */
    bool _isFirstMouseMove;
    float lastX;
    float lastY;
};