#include "DrawContext.h"
#include <iostream>

// TODO: keep track of scaling, rotation, translation in a list for each update.
// TODO: add copy() functionality
// TODO: add support for DrawContext and drawing children models.
Project::DrawContext::DrawContext(GLFWwindow* window) {
    _window = window;
    _shaderProgram = generateShaderProgram();
}

/**
 * Returns the window from which the drawing should be done on.
 **/
GLFWwindow* Project::DrawContext::getWindow() {
    return _window;
}


int Project::DrawContext::generateShaderProgram() {
    glEnable(GL_DEPTH_TEST);

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderSource = getVertexShaderSource();
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char log[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, log);
        std::cout << "ERROR - Shader - Vertex - Compiled Failed:\n" << log << std::endl;
        return -1;
    }

    const char* fragmentShaderSource = getFragmentShaderSource();
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, log);
        std::cout << "ERROR - Shader - Fragment - Compiled Failed:\n" << log << std::endl;
        return -1;
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, log);
        std::cout << "ERROR - Shader - Program - Compiled Failed:\n" << log << std::endl;
        return -1;
    }

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int Project::DrawContext::getShaderProgram() {
    return _shaderProgram;
}

const char* Project::DrawContext::getVertexShaderSource() {
    // TODO - Read from a .glsl file instead.
    return
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;"
        "layout (location = 1) in vec3 aColor;"
        "uniform mat4 worldMatrix;"
        "uniform mat4 viewMatrix = mat4(1.0);"  // default value for view matrix (identity)
        "uniform mat4 projectionMatrix = mat4(1.0);"
        ""
        "out vec3 vertexColor;"
        "void main()"
        "{"
        "   vertexColor = aColor;"
        "   mat4 modelViewProjection = projectionMatrix * viewMatrix * worldMatrix;"
        "   gl_Position = modelViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);"
        "}";
}

const char* Project::DrawContext::getFragmentShaderSource() {
    // TODO - Read from a .glsl file instead.
    return
        "#version 330 core\n"
        "in vec3 vertexColor;"
        "out vec4 FragColor;"
        "void main()"
        "{"
        "   FragColor = vec4(vertexColor.r, vertexColor.g, vertexColor.b, 1.0f);"
        "}";
}