#pragma once

#include <GLFW/glfw3.h>
#include "objects/Camera.h"

class Callbacks {
public:
    static void frameBufferSizeCallback(GLFWwindow*, int, int);
    static void mouseCallback(GLFWwindow*, double, double);
    static void errorCallback(int, const char*);
    static void setCamera(Camera* camera);
    static void setLastX(float lastX);
    static void setLastY(float lastY);
    static void setIsFirstMouseMove(bool isFirstMouseMove);

private:
    static bool isFirstMouseMove;
    static float lastX;
    static float lastY;
    static Camera* camera;
};
