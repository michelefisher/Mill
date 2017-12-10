cmake_minimum_required(VERSION 3.8)
project(Mill2)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp)
add_executable(Mill2 ${SOURCE_FILES})
target_link_libraries(Mill2 glfw glew soil ${OPENGL_LIBRARIES})
