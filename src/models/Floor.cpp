#pragma once
#include "Floor.h"



private:
const char* getVertexShaderSource()
{
    // For now, you use a string for your shader code, in the assignment, shaders will be stored in .glsl files
    return
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;"
        "layout (location = 1) in vec3 aColor;"
        ""
        "uniform mat4 worldMatrix;"
        "uniform mat4 viewMatrix = mat4(1.0);"
        "uniform mat4 projectionMatrix = mat4(1.0);"
        "out vec3 vertexColor;"
        "void main()"
        "{"
        "   vertexColor = aColor;"
        "   mat4 modelViewProjection = projectionMatrix * viewMatrix * worldMatrix;"
        "   gl_Position = modelViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);"
        "}";
}


const char* getFragmentShaderSource()
{
    return
        "#version 330 core\n"
        "in vec3 vertexColor;"
        "out vec4 FragColor;"
        "void main()"
        "{"
        "   FragColor = vec4(vertexColor.r, vertexColor.g, vertexColor.b, 1.0f);"
        "}";
}


int compileAndLinkShaders()
{
    // compile and link shader program
    // return shader program id
    // ------------------------------------

    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderSource = getVertexShaderSource();
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSource = getFragmentShaderSource();
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
int createFloorArrayObject()
{
    // A vertex is a point on a polygon, it contains positions and other data (eg: colors)
    glm::vec3 vertexArray[1444];
    for (int i = 0; i < 516; i += 4) {
        vertexArray[i] = glm::vec3(-1 + (i / 4) * coord, -0.01f, -1.0f);
        vertexArray[(i + 1)] = glm::vec3(0.5f, 0.5f, 0.0f);
        vertexArray[(i + 2)] = glm::vec3(-1 + (i / 4) * coord, -0.01f, 1.0f);
        vertexArray[(i + 3)] = glm::vec3(0.5f, 0.5f, 0.0f);
        vertexArray[(i + 516)] = glm::vec3(-1.0f, -0.01f, -1 + (i / 4) * coord);
        vertexArray[(i + 517)] = glm::vec3(0.5f, 0.5f, 0.0f);
        vertexArray[(i + 518)] = glm::vec3(1.0f, -0.01f, -1 + (i / 4) * coord);
        vertexArray[(i + 519)] = glm::vec3(0.5f, 0.5f, 0.0f);
    }
    vertexArray[1032] = glm::vec3(0.0f, 0.0f, 0.0f);
    vertexArray[1033] = glm::vec3(0.0f, 1.0f, 0.0f);
    vertexArray[1034] = glm::vec3(0.0f, 7 * coord, 0.0f);
    vertexArray[1035] = glm::vec3(0.0f, 1.0f, 0.0f);
    vertexArray[1036] = glm::vec3(0.0f, 0.0f, 0.0f);
    vertexArray[1037] = glm::vec3(1.0f, 0.0f, 0.0f);
    vertexArray[1038] = glm::vec3(7 * coord, 0.0f, 0.0f);
    vertexArray[1039] = glm::vec3(1.0f, 0.0f, 0.0f);
    vertexArray[1040] = glm::vec3(0.0f, 0.0f, 0.0f);
    vertexArray[1041] = glm::vec3(0.0f, 0.0f, 1.0f);
    vertexArray[1042] = glm::vec3(0.0f, 0.0f, 7 * coord);
    vertexArray[1043] = glm::vec3(0.0f, 0.0f, 1.0f);
    vertexArray[1044] = glm::vec3(1.0f, 0.0f, 0.0f);
    vertexArray[1045] = glm::vec3(1.0f, 0.0f, 0.0f);
    for (int i = 4; i < 400; i += 4) {
        vertexArray[1042 + i] = glm::vec3(cos(2 * 3.1415f * i / 400), 0.0f, sin(2 * 3.1415f * i / 400));
        vertexArray[1043 + i] = glm::vec3(1.0f, 0.0f, 0.0f);
        vertexArray[1044 + i] = glm::vec3(cos(2 * 3.1415f * i / 400), 0.0f, sin(2 * 3.1415f * i / 400));
        vertexArray[1045 + i] = glm::vec3(1.0f, 0.0f, 0.0f);
    }
    vertexArray[1442] = glm::vec3(1.0f, 0.0f, 0.0f);
    vertexArray[1443] = glm::vec3(1.0f, 0.0f, 0.0f);

    // Create a vertex array
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);


    // Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

    glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
        3,                   // size
        GL_FLOAT,            // type
        GL_FALSE,            // normalized?
        2 * sizeof(glm::vec3), // stride - each vertex contain 2 vec3 (position, color)
        (void*)0             // array buffer offset
    );
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1,                            // attribute 1 matches aColor in Vertex Shader
        3,
        GL_FLOAT,
        GL_FALSE,
        2 * sizeof(glm::vec3),
        (void*)sizeof(glm::vec3)      // color is offseted a vec3 (comes after position)
    );
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return vertexArrayObject;
}

public:
    void drawFloor() {
        static int shaderProgram = compileAndLinkShaders();
        static int vaofloor = createFloorArrayObject();
        glUseProgram(shaderProgram);


        glBindVertexArray(vaofloor);

        for (int i = 0; i < 722; i += 2)
            glDrawArrays(GL_LINE_LOOP, i, 2);
    }