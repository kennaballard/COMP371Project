#include "contexts/DrawContext.cpp"
#include "models/Model.cpp"
#include "managers/ModelManager.cpp"
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

    // Load needed services beforehand.
    auto manager = Project::ModelManager();
    Project::AlphanumbericalModelFactory factory = Project::AlphanumbericalModelFactory();
   /* manager.addModel(0, factory.createModelFor('T'));
    auto m = factory.createModelFor('T');*/
    //manager.addModel(0, factory.createModelFor('S'));

    // Kennedy model
    manager.addModel(0, factory.createModelFor("ky40"));
    auto a = factory.createModelFor("ky40");
   /* manager.addModel(0, factory.createModelFor('Y'));
    auto b = factory.createModelFor('Y');
    manager.addModel(0, factory.createModelFor('4'));
    auto c = factory.createModelFor('4'); 
    manager.addModel(0, factory.createModelFor('0'));
    auto d = factory.createModelFor('0');*/

    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Entering Main Loop
    auto context = Project::DrawContext(window);
    while(!glfwWindowShouldClose(window))
    {
        // Each frame, reset color of each pixel to glClearColor
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        // Keep track of models to draw.
        std::vector<Project::Model*> models = manager.getModels(0);
        for (Project::Model *model : models) {
            std::cout << "INNNNNNNNNNNNNNNNNNt\n" << std::endl;
            (*model).Draw(context);
        }

        (*a).Draw(context);
        /*(*b).Draw(context);
        (*c).Draw(context);
        (*d).Draw(context);*/

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