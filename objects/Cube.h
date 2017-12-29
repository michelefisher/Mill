#pragma once

#include "BasicObject.h"

class Cube : public BasicObject {
public:
    Cube();
    Cube(float);
    Cube(float, ShaderProgram*, Camera*);
};

