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
    auto s = new ModelSamuel(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f));
    auto c = new ModelY(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f));
    (*a).Draw(context);
    (*s).Draw(context);
    

   // a->setRotation(glm::vec3(-0.75f, -2.0f, 0.0f));
    //a->setScaling(glm::vec3(0.5f, 0.5f, 0.5f));
    //a->setPosition(glm::vec3(0.0f, 1.0f, 0.0f));
    //a->setTranslation(glm::vec3(0.5f, 1.0f, 0.0f));
   
    int shaderProgram = context.getShaderProgram();
    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Set projection matrix for shader, this won't change
    glm::mat4 projectionMatrix = glm::perspective(70.0f,            // field of view in degrees
                                                  800.0f / 600.0f,  // aspect ratio
                                                  0.01f, 100.0f);   // near and far (near > 0)

    GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

   //value use for a smooth rotations
    float angle = 0;
    float rotationSpeed = 180.0f;  // 180 degrees per second
    float lastFrameTime = glfwGetTime();

    //Value use to detect a key press only one time
    int lastKeyAPress = GLFW_RELEASE;
    int lastKeyDPress = GLFW_RELEASE;

    // Entering Main Loop
    

    while(!glfwWindowShouldClose(window))
    {
        

        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;
        // Each frame, reset color of each pixel to glClearColor
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        // Keep track of models to draw.
       /* std::vector<Project::Model*> models = manager.getModels(0);
        for (Project::Model *model : models) {
            std::cout << "INNNNNNNNNNNNNNNNNNt\n" << std::endl;
            (*model).Draw(context);
        }*/
        
        (*s).Draw(context);

        // End frame
        glfwSwapBuffers(window);
        
        // Detect inputs
        glfwPollEvents();
        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Samuel Rotation control 
        //detect if CTRL is press to change between smooth rotation or only 5 deegres per click 
        bool autorotations = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS;
        if (autorotations) {
            
            //Rotation left smooth
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                s->setRotation(glm::vec3(1.0f, 0.0f, 0.0f), rotationSpeed, dt);
                
            }
            //Rotation Right smooth
            else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                s->setRotation(glm::vec3(0.0f, 1.0f, 0.0f), -rotationSpeed, dt);

            }
        }
        else {
            // Left and right single click rotation
            if (lastKeyAPress == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
                s->setRotation(glm::vec3(0.0f, 1.0f, 0.0f),5.0f);
            
            }
            else if (lastKeyDPress == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
                s->setRotation(glm::vec3(0.0f, 1.0f, 0.0f), -5.0f);

            }
            lastKeyAPress = glfwGetKey(window, GLFW_KEY_A);
            lastKeyDPress = glfwGetKey(window, GLFW_KEY_D);
        }
        
 
           
    }
    
    // Shutdown GLFW
    glfwTerminate();
    
	return 0;
}