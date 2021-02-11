#pragma once
#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Project {
    /**
     * This is to keep track of the window used to draw models in.
     * 
     **/
    class DrawContext {
        private:
        GLFWwindow* _window;
        int _shaderProgram;

        public:
        // TODO: keep track of scaling, rotation, translation in a list for each update.
        // TODO: add copy() functionality
        // TODO: add support for DrawContext and drawing children models.
        DrawContext(GLFWwindow* window);

        /**
         * Returns the window from which the drawing should be done on.
         **/
        GLFWwindow* getWindow();

        /**
         * Returns the shader
         **/

        int generateShaderProgram();
        
        /**
         * Returns the shader
         **/
        int getShaderProgram();
        
        const char* getVertexShaderSource();

        const char* getFragmentShaderSource();
    };
}