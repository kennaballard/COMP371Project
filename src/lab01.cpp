//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 20/06/2019.
//
// Inspired by the following tutorials:
// - https://learnopengl.com/Getting-started/Hello-Window
// - https://learnopengl.com/Getting-started/Hello-Triangle

#include "contexts/DrawContext.h"
#include "models/Model.h"
#include "managers/ModelManager.h"
#include "managers/InputManager.h"
#include "factories/AlphanumericalModelFactory.h"
#include <string>


/*#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
                        // initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
*/

/*const char* getVertexShaderSource()
{
    // TODO - Insert Vertex Shaders here ...
    // For now, you use a string for your shader code, in the assignment, shaders will be stored in .glsl files
    return R"(#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
})";
}


const char* getFragmentShaderSource()
{
    // TODO - Insert Fragment Shaders here ...
    return R"(#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} )";
}


int compileAndLinkShaders()
{
    // TODO
    // compile and link shader program
    // return shader program id
    // ------------------------------------
    const char *vertexShaderSource = getVertexShaderSource();
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
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

    const char *fragmentShaderSource = getFragmentShaderSource();
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

int createVertexArrayObject()
{
    // TODO
    // Upload geometry to GPU and return the Vertex Buffer Object ID
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    // 0. copy our vertices array in a buffer for OpenGL to use
    /*glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 1. then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  
    // 2. use our shader program when we want to render an object
    glUseProgram(shaderProgram);*
    glEnableVertexAttribArray(0);
    return -1;
}*/

GLFWwindow* setup() {
    // Initialize GLFW and OpenGL version
    glfwInit();

#if defined(PLATFORM_OSX)	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
	// On windows, we set OpenGL version to 2.1, to support more hardware
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#endif

    // Create a 1024x768 window and the rendering context using GLFW.
    GLFWwindow* window = glfwCreateWindow(1024, 768, "Comp371 - Project", NULL, NULL);
    if (window == NULL)
    {
        //std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        //std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return NULL;
    }
    return window;
}

int main(int argc, char*argv[])
{
    GLFWwindow* window = setup();
    if (window == NULL) {
        return -1;
    }

    // Load needed services beforehand.
    Project::ModelManager manager = Project::ModelManager();
    Project::AlphanumbericalModelFactory factory = Project::AlphanumbericalModelFactory();
    manager.addModel(0, *factory.createModelFor('T'));
    manager.addModel(0, *factory.createModelFor('S'));

    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Entering Main Loop
    Project::DrawContext context = Project::DrawContext(window);
    while(!glfwWindowShouldClose(window))
    {
        // Each frame, reset color of each pixel to glClearColor
        glClear(GL_COLOR_BUFFER_BIT);

        // Keep track of models to draw.
        std::vector<Project::Model> models = manager.getModels(0);
        for (Project::Model model : models) {
            model.Draw(context);
        }

        // End frame
        glfwSwapBuffers(window);
        
        // Detect inputs
        glfwPollEvents();
        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

/*
    // Compile and link shaders here ...
    int shaderProgram = compileAndLinkShaders();
    
    // Define and upload geometry to the GPU here ...
    int vao = createVertexArrayObject();
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };
    
    // Entering Main Loop
    while(!glfwWindowShouldClose(window))
    {
        // Each frame, reset color of each pixel to glClearColor
        glClear(GL_COLOR_BUFFER_BIT);
        
        // TODO - draw rainbow triangle
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // End frame
        glfwSwapBuffers(window);
        
        // Detect inputs
        glfwPollEvents();
        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }*/
    
    // Shutdown GLFW
    glfwTerminate();
    
	return 0;
}