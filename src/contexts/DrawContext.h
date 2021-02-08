#pragma once
#include <vector>
#include "TransformationContext.cpp"

namespace Project {
    /**
     * This is to keep track of the window used to draw models in.
     **/
    class DrawContext {
        protected:
        GLFWwindow* _window;
        std::vector<Project::TransformationContext> _transformations;
        // Application specific.
        int _modelId;

        public:
        DrawContext(GLFWwindow* window);

        /**
         * Returns the model id for user input.
         * 
         * @return model id to perform user input on.
         **/
        int getModelId();

        /**
         * Returns the window from which the drawing should be done on.
         * 
         * @return the window used
         **/
        GLFWwindow* getWindow();

        /**
         * Pushes a transformation context onto the stack.
         * 
         * @param translation the translation transformation executed on this context.
         * @param rotation the rotation transformation executed on this context.
         * @param scale the scaling transformation exected on this context.
         **/
        void push(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale);

        /**
         * Pops the translation context off the stack.
         * 
         * @return the transformation context popped.
         **/
        Project::TransformationContext pop();

        /**
         * Peeks at the translation context at the top of the stack.
         * 
         * @return the transformation context peeked at.
         **/
        Project::TransformationContext peek();
    };
}