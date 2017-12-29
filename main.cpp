#include <iostream>
#include <vector>
#include <SOIL/soil.h>
#include "Application.h"
#include "objects/Cube.h"
#include "objects/Plane.h"

using namespace std;

int main() {
    unsigned const WIDTH = 800;
    unsigned const HEIGHT = 600;
    string applicationName = "Mill";

    Application application(WIDTH, HEIGHT, applicationName);

    /* vector<GLfloat> vertices = {
            -0.5f, 0.0f, -100.0f,     // far left
            0.5f, 0.0f, -100.0f,     // far right
            -0.5f, 0.0f, 100.0f,     // near left
            0.5f, 0.0f, 100.0f     // near right
    };


    vector<GLfloat> texturesCoords = {
            0.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f
    };

    vector<GLuint> indicies = {
            0, 1, 2,
            3, 2, 1
    }; */

    GLuint texture1 = SOIL_load_OGL_texture(
            "/Users/dominiktrusinski/Programowanie/GKOM/Mill2/container.jpg",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS
    );

    ShaderProgram textureShader("/Users/dominiktrusinski/Programowanie/GKOM/Mill2/shaders/shader.vert",
                                "/Users/dominiktrusinski/Programowanie/GKOM/Mill2/shaders/shader.frag");

    ShaderProgram colorShader("/Users/dominiktrusinski/Programowanie/GKOM/Mill2/shaders/color.vert",
                                "/Users/dominiktrusinski/Programowanie/GKOM/Mill2/shaders/color.frag");

    Cube cube(1.0f, &textureShader, &application.getCamera());
    cube.bindTexture(texture1, 0);

    application.addObjectToScene(&cube);

    Plane plane(100.0f, glm::vec3(0.0f, 0.292f, 0.0f), &colorShader, &application.getCamera());
    plane.bindTexture(texture1, 0);

    application.addObjectToScene(&plane);

    application.run();

    return 0;
}
