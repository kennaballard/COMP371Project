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
    manager.addModel(0, factory.createModelFor("al48"));
    auto b = factory.createModelFor("al48");
    manager.addModel(0, factory.createModelFor("ts47"));
    //auto a = factory.createModelFor("ky40");
    auto a = factory.createModelFor("ts47");
    //a->setScaling(glm::vec3(0.25f, 0.25f, 0.25f));
    //a->setScaling(glm::vec3(0.5f, 0.5f, 0.5f));
    //a->setPosition(glm::vec3(0.0f, 1.0f, 0.0f));
    //a->setTranslation(glm::vec3(0.5f, 1.0f, 0.0f));



    manager.addModel(0, factory.createModelFor("ae20"));
    auto c = factory.createModelFor("ae20");

    manager.addModel(0, factory.createModelFor("floor"));
    auto floor = factory.createModelFor("floor");

    b->setScaling(glm::vec3(0.5f, 0.5f, 0.5f));
    b->setTranslation(glm::vec3(0.5f, 1.0f, 0.0f));
    b->setPosition(glm::vec3(0.0f, 1.0f, 0.0f));
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


    //variables for frame movement
    float rotationSpeed = 180.0f;  // 180 degrees per second
    float lastFrameTime = glfwGetTime();
    float movementSpeed = 0.5f;

    //initialize view
    glm::mat4 view_matrix;
    view_matrix = glm::lookAt(eye, center, up);
    glm::vec3 eye(1.0f);
    glm::vec3 center(0.0f, 0.0f, -0.5f);

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

        //Frame time calculation
        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;

        // Keep track of models to draw.
       /* std::vector<Project::Model*> models = manager.getModels(0);
        for (Project::Model *model : models) {
            std::cout << "INNNNNNNNNNNNNNNNNNt\n" << std::endl;
            (*model).Draw(context);
        }*/
        (*floor).Draw(context);
        
        //draw ModelKennedy
        // Draw models
        (*a).Draw(context);

        //draw ModelAna
        (*b).Draw(context);

        (*c).Draw(context);

        // End frame
        glfwSwapBuffers(window);

        // Detect inputs
        glfwPollEvents();

        /////////////////////////
        //                     //
        //   Keyboard Input    //
        //                     //
        ////////////////////////

        //close window
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        }

        //scale up 
        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {

            a->setScaling(glm::vec3(dt+0.6f, dt+0.6f, dt+0.6));
        }

        //scale down
        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {

            a->setScaling(glm::vec3(dt+0.4f, dt+0.4f, dt+0.4f)); 
        }


        //show line view 
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        //show point view 
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {

            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        }
        //show triangle view 
        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        //orientation right 
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            glm::vec3 direction(-0.5f, 0.0f, 0.0f);
            eye = eye + direction * movementSpeed * dt;
            center = center + direction * movementSpeed * dt;

            glm::mat4 viewMatrix = glm::lookAt(eye,  // eye
                center,  // center
                glm::vec3(0.0f, 0.5f, 0.0f));// up

            GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
            glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
        }

        //orientation left
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            glm::vec3 direction(0.5f, 0.0f, 0.0f);
            eye = eye + direction * movementSpeed * dt;
            center = center + direction * movementSpeed * dt;

            glm::mat4 viewMatrix = glm::lookAt(eye,  // eye
                center,  // center
                glm::vec3(0.0f, 0.5f, 0.0f));// up

            GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
            glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
        }

        //orientation down
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            glm::vec3 direction(0.0f, 0.5f, 0.0f);
            eye = eye + direction * movementSpeed * dt;
            center = center + direction * movementSpeed * dt;

            glm::mat4 viewMatrix = glm::lookAt(eye,  // eye
                center,  // center
                glm::vec3(0.0f, 0.5f, 0.0f));// up

            GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
            glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
        }

        //orientation up
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            glm::vec3 direction(0.0f, -0.5f, 0.0f);
            eye = eye + direction * movementSpeed * dt;
            center = center + direction * movementSpeed * dt;

            glm::mat4 viewMatrix = glm::lookAt(eye,  // eye
                center,  // center
                glm::vec3(0.0f, 0.5f, 0.0f));// up

            GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
            glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
        }

        //reset initial world position
        if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS)
        {

            auto camera = Project::Camera(cameraPosition, cameraLookAt, cameraUp, glGetUniformLocation(context.getShaderProgram(), "viewMatrix"));
          //  auto cameraMatrix = camera.setupCamera(context);

            GLuint cameraMatrixLocation = glGetUniformLocation(context.getShaderProgram(), "viewMatrix");
         //   glUniformMatrix4fv(cameraMatrixLocation, 1, GL_FALSE, &cameraMatrix[0][0]);

        }
    }

    // Shutdown GLFW
    glfwTerminate();

    return 0;
};