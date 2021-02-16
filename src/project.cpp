#include "contexts/DrawContext.cpp"
#include "models/Model.cpp"
#include "managers/ModelManager.cpp"
#include "inputs/mouse/MouseCursorHandler.cpp"
#include "inputs/mouse/MouseButtonHandler.cpp"
#include "cameras/Camera.cpp"
//#include "managers/InputManager.h"
#include "factories/AlphanumericalModelFactory.cpp"
#include <string>
#include <vector>


const char* TITLE = "COMP 371 - Project - Team 3";

float xScale = 0.01f;
float yScale = 0.01f;
float zScale = 0.01f;

glm::vec3 scale_vec = glm::vec3(0.0f, 0.0f, 0.0f);

// Constant vectors
const glm::vec3 center(0.0f, 0.0f, -0.5f);
const glm::vec3 up(0.0f, 0.5f, 0.0f);
glm::vec3 eye(0.0f, 0.0f, -0.5f);


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

std::vector<Project::Camera*> setupCameras(std::vector<Project::Model*> models, Project::DrawContext context) {
    std::vector<Project::Camera*> cameras = std::vector<Project::Camera*>();
    
    glm::vec3 defaultPosition(0.6f, 0.0f, 5.0f);
    glm::vec3 defaultLookAt(0.0f, 0.0f, -1.0f);
    glm::vec3 defaultUp(0.0f, 1.0f, 0.0f);

    // For each model, setup a camera
    for (Project::Model* model : models) {
        glm::vec3 modelPos = model->getPosition();
        auto newCamera = new Project::Camera(defaultPosition + modelPos, defaultLookAt, defaultUp, glGetUniformLocation(context.getShaderProgram(), "viewMatrix"));
        newCamera->setupCamera(context);
        cameras.push_back(newCamera);
    }

    return cameras;
}

const float circlePosX = 20;
const float circlePosZ = 20;
int main(int argc, char*argv[])
{
    GLFWwindow* window = setup();
    if (window == NULL) {
        return -1;
    }

    auto context = Project::DrawContext(window);
    int shaderProgram = context.getShaderProgram();

   
    // Load needed services beforehand.
    auto manager = Project::ModelManager();
    Project::AlphanumbericalModelFactory factory = Project::AlphanumbericalModelFactory();
  
    // --------- Models
    auto kennedyModel = factory.createModelFor("ky40");
    auto anaModel = factory.createModelFor("al48");
    auto thomasModel = factory.createModelFor("ts47");
    auto antoineModel = factory.createModelFor("ae20");

    // Displace models and create their own cameras
    thomasModel->setPosition(glm::vec3(-circlePosX, 0.0f, circlePosZ));
    anaModel->setPosition(glm::vec3(circlePosX, 0.0f, circlePosZ));
    antoineModel->setPosition(glm::vec3(-circlePosX, 0.0f, -circlePosZ));

    std::vector<Project::Model*> models = std::vector<Project::Model*>();
    // Kennedy
    models.push_back(kennedyModel);
    // Antoine
    models.push_back(antoineModel);
    // Thomas
    models.push_back(thomasModel);
    // Ana
    models.push_back(anaModel);

    // Set the current 
    Project::Model* activeModel = models.at(0);

    auto floor = factory.createModelFor("floor");

    // --------- Camera
    // Setup for each model
    std::vector<Project::Camera*> cameras = setupCameras(models, context);

    // Current camera
    auto activeCamera = cameras.at(0);
    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


    // --------- Projection Matrix
    // This won't change
    glm::mat4 projectionMatrix = glm::perspective(70.0f,            // field of view in degrees
        800.0f / 600.0f,  // aspect ratio
        0.01f, 100.0f);   // near and far (near > 0)

    GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);


    //variables for frame movement 
    float lastFrameTime = glfwGetTime();
    float movementSpeed = 0.5f;

    //initialize view
    glm::mat4 view_matrix = glm::lookAt(eye, center, up);
    glm::vec3 eye(1.0f);
    glm::vec3 center(0.0f, 0.0f, -0.5f);

    // --------- Input Handling
    mouseButtonHandler = new Project::MouseButtonHandler(context);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
   
    // Entering Main Loop
    while(!glfwWindowShouldClose(window))
    {  
        // Each frame, reset color of each pixel to glClearColor
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        //Frame time calculation
        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;

        // Calculate camera pos
        activeCamera->calculatePosition(context, mouseButtonHandler);

        // Draw all models
        floor->Draw(context);

        for (Project::Model* model : models) {
            model->Draw(context);
        }

        // End frame
        glfwSwapBuffers(window);

        // Detect inputs
        glfwPollEvents();


        // --------- close window
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        
        // --------- Focus Model/Camera
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            // Select the first model (Pos 0)
            activeModel = models.at(0);
            activeCamera = cameras.at(0);
        }

        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            // Select the second model (Pos 1)
            activeModel = models.at(1);
            activeCamera = cameras.at(1);
        }

            glm::vec3 scale = glm::vec3(0.01f, 0.01f, 0.01f);
            if (scale_vec.x >= 0.5 && scale_vec.y >= 0.5 && scale_vec.z >= 0.5) {
                scale_vec.x += scale.x;
                scale_vec.y += scale.y;
                scale_vec.z += scale.z;
                a->setScaling(glm::vec3(scale_vec.x, scale_vec.y, scale_vec.z));
            }
            else {
                scale_vec.x = 0.5f;
                scale_vec.y = 0.5f;
                scale_vec.z = 0.5f;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
            // Select the fourth model (Pos 3)
            activeModel = models.at(3);
            activeCamera = cameras.at(3);
        }
        //if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        //    // Select the fifth model (Pos 3)
        //    activeModel = models.at(3);
        //    activeCamera = cameras.at(3);
        //}


            glm::vec3 scale = glm::vec3(0.01f, 0.01f, 0.01f);
            if (scale_vec.x >= 0.5 && scale_vec.y >= 0.5 && scale_vec.z >= 0.5) {
                scale_vec.x -= scale.x;
                scale_vec.y -= scale.y;
                scale_vec.z -= scale.z;
                a->setScaling(glm::vec3(scale_vec.x, scale_vec.y, scale_vec.z));
            }
            else {
                scale_vec.x = 0.5f;
                scale_vec.y = 0.5f;
                scale_vec.z = 0.5f;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
            // scale up
            activeModel->setScaling(glm::vec3(dt+0.4f, dt+0.4f, dt+0.4f)); 
        }

        // --------- Draw format
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
            // Lines
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
       
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
            // Points
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        }
        
        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
            // Filled 
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        // --------- Camera Orientation
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            //glm::vec3 direction(-0.5f, 0.0f, 0.0f);
            //eye = eye + direction * movementSpeed * dt;
            //center = center + direction * movementSpeed * dt;

            //glm::mat4 viewMatrix = glm::lookAt(eye,  // eye
            //    center,  // center
            //    glm::vec3(0.0f, 0.5f, 0.0f));// up

            //GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
            //glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            //glm::vec3 direction(0.5f, 0.0f, 0.0f);
            //eye = eye + direction * movementSpeed * dt;
            //center = center + direction * movementSpeed * dt;

            //glm::mat4 viewMatrix = glm::lookAt(eye,  // eye
            //    center,  // center
            //   glm::vec3(0.0f, 0.5f, 0.0f));// up

            //GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
            //glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
        }

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            //glm::vec3 direction(0.0f, 0.5f, 0.0f);
            //eye = eye + direction * movementSpeed * dt;
            //center = center + direction * movementSpeed * dt;

            //glm::mat4 viewMatrix = glm::lookAt(eye,  // eye
            //    center,  // center
            //    glm::vec3(0.0f, 0.5f, 0.0f));// up

            //GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
            //glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
        }

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            //glm::vec3 direction(0.0f, -0.5f, 0.0f);
            //eye = eye + direction * movementSpeed * dt;
            //center = center + direction * movementSpeed * dt;

            //glm::mat4 viewMatrix = glm::lookAt(eye,  // eye
            //    center,  // center
            //    glm::vec3(0.0f, 0.5f, 0.0f));// up

            /*GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
            glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);*/
        }

        // --------- reset initial world position
        if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS)
        {
            //TODO: reset camera position

        }
    }

    // Shutdown GLFW
    glfwTerminate();

    return 0;
};