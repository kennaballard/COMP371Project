#include "contexts/DrawContext.cpp"
#include "models/Model.cpp"
#include "managers/ModelManager.cpp"
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

int main(int argc, char*argv[])
{
    GLFWwindow* window = setup();
    if (window == NULL) {
        return -1;
    }

    auto context = Project::DrawContext(window);

    // Camera parameters for view transform
    glm::vec3 cameraPosition(0.6f, 0.0f, 5.0f);
    glm::vec3 cameraLookAt(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

    // Camera intialization
    auto camera = Project::Camera(cameraPosition, cameraLookAt, cameraUp);
    auto cameraMatrix = camera.setupCamera(context);

    GLuint cameraMatrixLocation = glGetUniformLocation(context.getShaderProgram(), "viewMatrix");
    glUniformMatrix4fv(cameraMatrixLocation, 1, GL_FALSE, &cameraMatrix[0][0]);

    // Load needed services beforehand.
    auto manager = Project::ModelManager();
    Project::AlphanumbericalModelFactory factory = Project::AlphanumbericalModelFactory();
  

    // Kennedy model
    manager.addModel(0, factory.createModelFor("ky40"));
    auto a = factory.createModelFor("ky40");
    //a->setScaling(glm::vec3(0.5f, 0.5f, 0.5f));
    //a->setPosition(glm::vec3(0.0f, 1.0f, 0.0f));
    //a->setTranslation(glm::vec3(0.5f, 1.0f, 0.0f));

    //Ana model
    manager.addModel(0, factory.createModelFor("al48"));
    auto b = factory.createModelFor("al48");
    //b->setScaling(glm::vec3(0.5f, 0.5f, 0.5f));
    //b->setPosition(glm::vec3(0.0f, 1.0f, 0.0f));
    //b->setTranslation(glm::vec3(0.5f, 1.0f, 0.0f));
   
    int shaderProgram = context.getShaderProgram();
    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Set projection matrix for shader, this won't change
    glm::mat4 projectionMatrix = glm::perspective(70.0f,            // field of view in degrees
                                                  800.0f / 600.0f,  // aspect ratio
                                                  0.01f, 100.0f);   // near and far (near > 0)

    GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

   

    // Entering Main Loop
   
    while(!glfwWindowShouldClose(window))
    {
        
        // Each frame, reset color of each pixel to glClearColor
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        // Keep track of models to draw.
       /* std::vector<Project::Model*> models = manager.getModels(0);
        for (Project::Model *model : models) {
            std::cout << "INNNNNNNNNNNNNNNNNNt\n" << std::endl;
            (*model).Draw(context);
        }*/
        
        //draw ModelKennedy
        (*a).Draw(context);

        //draw ModelAna
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
}