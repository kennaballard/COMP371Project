#pragma once
#include "../contexts/DrawContext.h"
#include <vector>

namespace Project {
    /**
     * Models each have their own shader program and buffer object.
     * While that is slower than placing them all together, it facilitates
     * drawing several objects that have no relation to each other.
     **/
    class Model {
        private:
        glm::vec3 _position;
        glm::vec3 _rotation;
        glm::vec3 _scale;
        bool _reflectionX;
        bool _reflectionY;
        bool _reflectionZ;
        std::vector<Model*> _children;
        
        protected:
        /**
         * Draws the model with the assumption that the scale is 1:1
         * and the model is "standing" (parallel to the Y-axis).
         **/
        virtual void drawModel(Project::DrawContext context)=0;
        //virtual void updateModel(Project::DrawContext context)=0;

        public:
        Model(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

        /**
         * Draws the model and takes translation, rotation and scaling
         * into account.
         * 
         * @param context the drawing context used
         **/
        void draw(Project::DrawContext context);

        /**
         * Returns the fully compiled shader program for this model.
         **/
        virtual int getShaderProgram()=0;

        /**
         * Returns the vertex buffer object for this model.
         **/
        virtual int getVertexBufferObject()=0;

        /**
         * Sets the totation for each of its corresponding axis.
         **/
        void rotate(glm::vec3 scale);

        /**
         * Sets the scaling for each of its corresponding axis.
         **/
        void scale(glm::vec3 scale);

        /**
         * Sets the translation for each of its corresponding axis.
         **/
        void translate(glm::vec3 scale);

        private:
        /**
         * Returns the vertex shader program code.
         * 
         * @return the code for the vertex shader program.
         **/
        virtual const char* Model::getVertexShaderSource()=0;

        /**
         * Returns the fragment shader program code.
         * 
         * @return the code for the fragment shader program.
         **/
        virtual const char* Model::getFragmentShaderSource()=0;
    };
}