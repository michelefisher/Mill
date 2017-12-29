#pragma once

class Timer {
public:
    Timer();
    void updateDeltaTime();
    float getDeltaTime();
private:
    float lastFrame;
    float deltaTime;
};