#include <iostream>
#include <GL/glew.h>
#include <SOIL/soil.h>
#include "Application.h"
#include "objects/ColoredCube.h"
#include "objects/Plane.h"
#include "objects/Light.h"

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

    ShaderProgram lightShader("/Users/dominiktrusinski/Programowanie/GKOM/Mill2/shaders/light.vert",
                                "/Users/dominiktrusinski/Programowanie/GKOM/Mill2/shaders/light.frag");

    ShaderProgram textureShader("/Users/dominiktrusinski/Programowanie/GKOM/Mill2/shaders/shader.vert",
                                "/Users/dominiktrusinski/Programowanie/GKOM/Mill2/shaders/shader.frag");

    ShaderProgram colorShader("/Users/dominiktrusinski/Programowanie/GKOM/Mill2/shaders/color.vert",
                                "/Users/dominiktrusinski/Programowanie/GKOM/Mill2/shaders/color.frag");

    Light light(&lightShader, &application.getCamera(), glm::vec3(1.0f, 1.0f, 1.0f));
    light.translate(glm::vec3(0.0f, 3.0f, 0.0f));
    application.addObjectToScene(&light);


    Plane plane(&colorShader, &application.getCamera(), 100.0f, glm::vec3(0.5f, 0.5f, 0.5f));
    plane.setLightColor(light.getLightColor());
    application.addObjectToScene(&plane);

    ColoredCube cube(&colorShader, &application.getCamera(), 1.0f, glm::vec3(1.0f, 0.5f, 0.5f));
    cube.setLightColor(light.getLightColor());
    application.addObjectToScene(&cube);

    ColoredCube cube1(&colorShader, &application.getCamera(), 1.0f, glm::vec3(1.0f, 0.5f, 1.0f));
    cube1.translate(glm::vec3(3.0f,0.0f, 2.0f));
    cube1.setLightColor(light.getLightColor());
    application.addObjectToScene(&cube1);

    application.run();

    return 0;
}
