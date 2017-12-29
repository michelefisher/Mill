#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "Plane.h"

//0.133, 0.545, 0.133

Plane::Plane(float width, glm::vec3 color) : Cube(width) {
    //model = glm::translate(model, glm::vec3(0.0f, -red, green, blue));
    //model = glm::scale(model, glm::vec3(1.0f, 0.001f, 1.0f));

    float red = color.x;
    float green = color.y;
    float blue = color.z;

    vertices = {
            -0.5f*width, -0.001f, -0.5f*width,  red, green, blue,
            0.5f*width, -0.001f, -0.5f*width,  red, green, blue,
            0.5f*width,  0.001f, -0.5f*width,  red, green, blue,
            -0.5f*width,  0.001f, -0.5f*width,  red, green, blue,

            -0.5f*width, -0.001f,  0.5f*width,  red, green, blue,
            0.5f*width, -0.001f,  0.5f*width,  red, green, blue,
            0.5f*width,  0.001f,  0.5f*width,  red, green, blue,
            -0.5f*width,  0.001f,  0.5f*width,  red, green, blue,

            -0.5f*width,  0.001f,  0.5f*width,  red, green, blue,
            -0.5f*width,  0.001f, -0.5f*width,  red, green, blue,
            -0.5f*width, -0.001f, -0.5f*width,  red, green, blue,
            -0.5f*width, -0.001f,  0.5f*width,  red, green, blue,

            0.5f*width,  0.001f,  0.5f*width,  red, green, blue,
            0.5f*width,  0.001f, -0.5f*width,  red, green, blue,
            0.5f*width, -0.001f, -0.5f*width,  red, green, blue,
            0.5f*width, -0.001f,  0.5f*width,  red, green, blue,

            -0.5f*width, -0.001f, -0.5f*width,  red, green, blue,
            0.5f*width, -0.001f, -0.5f*width,  red, green, blue,
            0.5f*width, -0.001f,  0.5f*width,  red, green, blue,
            -0.5f*width, -0.001f, -0.5f*width,  red, green, blue,

            -0.5f*width,  0.001f, -0.5f*width,  red, green, blue,
            0.5f*width,  0.001f, -0.5f*width,  red, green, blue,
            0.5f*width,  0.001f,  0.5f*width,  red, green, blue,
            -0.5f*width,  0.001f,  0.5f*width,  red, green, blue,
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(GLfloat), &this->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Plane::Plane(float width, glm::vec3 color, ShaderProgram* shaderProgram, Camera* camera) : Plane(width, color) {
    this->shaderProgram = shaderProgram;
    this->camera = camera;
}