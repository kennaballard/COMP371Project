#include "contexts/DrawContext.cpp"
#include "models/Model.cpp"
#include "managers/ModelManager.cpp"
#include "inputs/mouse/MouseCursorHandler.cpp"
#include "inputs/mouse/MouseButtonHandler.cpp"
#include "cameras/Camera.cpp"
//#include "managers/InputManager.h"
#include "factories/AlphanumericalModelFactory.cpp"
#include <string>



const char* TITLE = "COMP 371 - Project - Team 3";



GLFWwindow* setup() {
    // Initialize GLFW and OpenGL version
    glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create a 1024x768 window and the rendering context using GLFW.
    GLFWwindow* window = glfwCreateWindow(1024, 768, TITLE, NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return NULL;
    }
    return window;
}


Project::MouseButtonHandler* mouseButtonHandler;
Project::MouseCursorHandler* mouseCursorHandler;
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    mouseButtonHandler->handle(window, button, action, mods);
}

void cursorCallback(GLFWwindow* window, double xpos, double ypos) {
    mouseCursorHandler->handle(window, xpos, ypos);
}

void cameraPositioning() {

}

int main(int argc, char*argv[])
{
    GLFWwindow* window = setup();
    if (window == NULL) {
        return -1;
    }

    auto context = Project::DrawContext(window);

    // --------- Camera

    // Camera parameters for view transform
    glm::vec3 cameraPosition(0.6f, 0.0f, 5.0f);
    glm::vec3 cameraLookAt(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

    // Camera intialization
    auto camera = Project::Camera(cameraPosition, cameraLookAt, cameraUp, glGetUniformLocation(context.getShaderProgram(), "viewMatrix"));
    camera.setupCamera(context);

    // Set as active camera
    // TODO

    // Load needed services beforehand.
    auto manager = Project::ModelManager();
    Project::AlphanumbericalModelFactory factory = Project::AlphanumbericalModelFactory();
  
    // --------- Models
    // Kennedy model
    manager.addModel(0, factory.createModelFor("ky40"));
    manager.addModel(0, factory.createModelFor("ts47"));
    //auto a = factory.createModelFor("ky40");
    auto a = factory.createModelFor("ts47");
    //a->setScaling(glm::vec3(0.25f, 0.25f, 0.25f));
    //a->setScaling(glm::vec3(0.5f, 0.5f, 0.5f));
    //a->setPosition(glm::vec3(0.0f, 1.0f, 0.0f));
    //a->setTranslation(glm::vec3(0.5f, 1.0f, 0.0f));



    manager.addModel(0, factory.createModelFor("ae20"));
    auto b = factory.createModelFor("ae20");

    manager.addModel(0, factory.createModelFor("floor"));
    auto floor = factory.createModelFor("floor");

    int shaderProgram = context.getShaderProgram();
    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


    // --------- Projection Matrix
    // This won't change
    glm::mat4 projectionMatrix = glm::perspective(70.0f,            // field of view in degrees
        800.0f / 600.0f,  // aspect ratio
        0.01f, 100.0f);   // near and far (near > 0)

    GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

    // --------- Input Handling
    
    mouseButtonHandler = new Project::MouseButtonHandler(context);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
   
    // Entering Main Loop
    while(!glfwWindowShouldClose(window))
    {
        // Calculate camera pos
        camera.calculatePosition(context, mouseButtonHandler);
       
        // Each frame, reset color of each pixel to glClearColor
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        (*floor).Draw(context);
        
        // Draw models
        (*a).Draw(context);
        

        (*b).Draw(context);

        // End frame
        glfwSwapBuffers(window);

        // Detect inputs
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    // Shutdown GLFW
    glfwTerminate();

    return 0;
};