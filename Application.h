#pragma once

#include <string>
#include "Window.h"
#include "Timer.h"
#include "objects/Camera.h"
#include "objects/BasicObject.h"


class Application {
public:
    Application(unsigned, unsigned, const std::string&);

    void addObjectToScene(BasicObject*);
    void processInput(GLFWwindow*);
    void run();

    Camera& getCamera();

    unsigned const WINDOW_WIDTH;
    unsigned const WINDOW_HEIGHT;
private:
    void initGLFW();
    void initGLEW();
    const std::string APPLICATION_NAME;
    vector<BasicObject*> objectsToDraw;
    Window* window;
    Timer timer;
    Camera camera;
};