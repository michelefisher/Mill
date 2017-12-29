cmake_minimum_required(VERSION 3.8)
project(Mill2)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp ShaderProgram.h objects/BasicObject.h objects/BasicObject.cpp objects/Camera.h objects/Camera.cpp objects/CameraMovement.h Timer.cpp Timer.h Window.cpp Window.h Application.cpp Application.h Callbacks.cpp Callbacks.h objects/Cube.cpp objects/Cube.h ShaderProgram.cpp objects/Plane.cpp objects/Plane.h)
add_executable(Mill2 ${SOURCE_FILES})
target_link_libraries(Mill2 glfw glew soil ${OPENGL_LIBRARIES})
