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

const float circlePosX = 20;
const float circlePosZ = 20;
float deltaTime = 0.0f;

glm::vec3 scale_vec = glm::vec3(0.0f, 0.0f, 0.0f);

Project::MouseButtonHandler* mouseButtonHandler;
Project::MouseCursorHandler* mouseCursorHandler;

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


void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    mouseButtonHandler->handle(window, button, action, mods);
}

std::vector<Project::Camera*> setupCameras(std::vector<Project::Model*> models, Project::DrawContext context) {
    std::vector<Project::Camera*> cameras = std::vector<Project::Camera*>();
    
    glm::vec3 defaultPosition(0.6f, 1.0f, 5.0f);
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

    glm::vec3 prePosition = thomasModel->getPosition();

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
    float defaultFieldOfView = 70.0f;
    float aspectRatio = 800.0f / 600.0f;
    float near = 0.01f;
    float far = 100.0f;

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(defaultFieldOfView),            // field of view in degrees
        aspectRatio,  // aspect ratio
       near, far);   // near and far (near > 0)

    GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);


    //variables for frame movement 
    float lastFrameTime = glfwGetTime();
    float movementSpeed = 1.0f;
    float rotationSpeed = 180.0f;  // 180 degrees per second
    float angle = 0;
    

    // --------- Input Handling
    mouseButtonHandler = new Project::MouseButtonHandler(context);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
   
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Entering Main Loop
    while(!glfwWindowShouldClose(window))
    {  
        float cameraSpeed = 1.0 * deltaTime;

        // Each frame, reset color of each pixel to glClearColor
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        //Frame time calculation
        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;

        // Calculate camera pos
        activeCamera->calculatePosition(context, mouseButtonHandler);
        float newFieldOfView = activeCamera->getFieldOfView();

   

        projectionMatrix = glm::perspective(glm::radians(newFieldOfView), aspectRatio, near, far);
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

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
        
        // --------- Model Selection/Camera
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            activeCamera->resetPosition();
            // Select the first model (Pos 0)
            activeModel = models.at(0);
            activeCamera = cameras.at(0);
        }

        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            activeCamera->resetPosition();
            // Select the second model (Pos 1)
            activeModel = models.at(1);
            activeCamera = cameras.at(1);
        }

        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
            activeCamera->resetPosition();
            // Select the fourth model (Pos 2)
            activeModel = models.at(2);
            activeCamera = cameras.at(2);
        }


        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
            activeCamera->resetPosition();
            // Select the fourth model (Pos 3)
            activeModel = models.at(3);
            activeCamera = cameras.at(3);
        }

      
        //if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
       // activeCamera->resetPosition();
        //   // Select the fifth model (Pos 4)
        //   activeModel = models.at(4);
        //   activeCamera = cameras.at(4);
        //}


        //----------Scaling Selected Model
        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
            // scale up
            glm::vec3 scale = glm::vec3(0.01f, 0.01f, 0.01f);
            if (scale_vec.x >= 0.5 && scale_vec.y >= 0.5 && scale_vec.z >= 0.5) {
                scale_vec.x += scale.x;
                scale_vec.y += scale.y;
                scale_vec.z += scale.z;
                activeModel->setScaling(glm::vec3(scale_vec.x, scale_vec.y, scale_vec.z));
            }
            else {
                scale_vec.x = 0.5f;
                scale_vec.y = 0.5f;
                scale_vec.z = 0.5f;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
            // scale down
            glm::vec3 scale = glm::vec3(0.01f, 0.01f, 0.01f);
            if (scale_vec.x >= 0.5 && scale_vec.y >= 0.5 && scale_vec.z >= 0.5) {
                scale_vec.x -= scale.x;
                scale_vec.y -= scale.y;
                scale_vec.z -= scale.z;
                activeModel->setScaling(glm::vec3(scale_vec.x, scale_vec.y, scale_vec.z));
            }
            else {
                scale_vec.x = 0.5f;
                scale_vec.y = 0.5f;
                scale_vec.z = 0.5f;
            }
        }

        // --------- Render Mode
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
            //moveRight
            activeCamera->moveRight();
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            //moveLeft
            activeCamera->moveLeft();
        }

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            //moveDown 
            activeCamera->moveDown();  
        }

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            //moveUp
            activeCamera->moveUp();
        }

        if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS)
        {
           //reset initial world and model position
            kennedyModel->setPosition(glm::vec3(circlePosX, 0.0f, -circlePosZ));
            kennedyModel->setPosition(glm::vec3(0.0f, 0.0f, 0.0f)); //samuel model 
            anaModel->setPosition(glm::vec3(circlePosX, 0.0f, -circlePosZ));
            antoineModel->setPosition(glm::vec3(circlePosX, 0.0f, -circlePosZ));
            thomasModel->setPosition(glm::vec3(circlePosX, 0.0f, -circlePosZ));
            for (auto model : models) {
                model->setRotation(glm::vec3(0.0f, 0.0f, 0.0f), 0);
                model->setScaling(glm::vec3(1.0f, 1.0f, 1.0f));
            }
            activeCamera->resetPosition();
            activeCamera = cameras.at(0);
        }

        //---------Model position and orientation
        // Uppercase WASD translates
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
            glm::vec3 currentPos = activeModel->getPosition();

            // Move Left
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)                      
                currentPos.x -= movementSpeed * dt;
            
            // Move Right              
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)   
                currentPos.x += movementSpeed * dt;   

            // Move Down
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)           
                currentPos.y -= movementSpeed * dt;       
            
            // Move Up
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                currentPos.y += movementSpeed * dt;
            
            activeModel->setPosition(currentPos);
        }
        else
        {

            // Lowercase --> rotates ad
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
                //rotateLeft
                 activeModel->setRotation(glm::vec3(0.0f, 1.0f, 0.0f), rotationSpeed, dt);

            }

            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
                //rotateRight

            }

        }

    }

    // Shutdown GLFW
    glfwTerminate();

    return 0;
};