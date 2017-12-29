#include <iostream>
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

    Cube cube(&colorShader, &application.getCamera(), 1.0f, glm::vec3(0.0f, 0.5f, 0.0f));
    application.addObjectToScene(&cube);

    Plane plane(&colorShader, &application.getCamera(), 100.0f, glm::vec3(0.5f, 0.0f, 0.0f));
    //plane.bindTexture(texture1, 0);

    application.addObjectToScene(&plane);

    application.run();

    return 0;
}
