#include <GLFW/glfw3.h>
#include "Timer.h"

Timer::Timer() : lastFrame(0.0f), deltaTime(0.0f) {}

void Timer::updateDeltaTime() {
    float currentFrame = static_cast<float>(glfwGetTime());

    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

float Timer::getDeltaTime() {
    return deltaTime;
}
