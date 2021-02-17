#pragma once
#include "../contexts/DrawContext.h"
#include <vector>

namespace Project {
    /**
     * Models each have their own shader program and buffer object.
     * While that is slower than placing them all together, it facilitates
     * drawing several objects that have no relation to each other.
     * relative positions stores the children positions relative to parent
     **/
    class Model {
        private:
        glm::mat4 _parentMatrix;
        glm::vec3 _position;
        float _rotation;
        glm::vec3 _scale;
        std::vector<Model*> _children;
        std::vector<glm::vec3> _relativePositions;
        int _numChildren;
        int _vaoRef;

        protected:
        /**
         * Draws the model with the assumption that the scale is 1:1
         * and the model is "standing" (parallel to the Y-axis).
         **/
        virtual void DrawModel(Project::DrawContext context)=0;

        public:
        Model(glm::mat4 parentMatrix, glm::vec3 position, float rotation, glm::vec3 scale);

        /**
         * Draws the model and takes translation, rotation and scaling
         * into account.
         * 
         * @param context the drawing context used
         **/
        void Draw(Project::DrawContext context);

        /**
        * Returns reference int to the generated VBO.
        **/
        int getVertexBufferObject();
        void setVertexBufferObject(int vbo);

        /**
         * Add a child to the model
         **/
        void addChild(Model* model);

        /**
        * Set the current position.
        **/
       void setPosition(glm::vec3 position);
        /**
         * Get the current position.
         **/
        glm::vec3 getPosition();

        /**
         * Sets the scaling for each of its corresponding axis.
         **/
        void setScaling(glm::vec3 scale);

        /**
         * Gets the current scale factor
         **/
        glm::vec3 getScale();

        /**
        * Changes position by translation factor
        **/
        void setTranslation(glm::vec3 translation);

        /**
         * Changes position by translation factor
        **/
        void setRotation(float rotation);

        float getRotation();


        glm::mat4 getParentMatrix();
        void setParentMatrix(glm::mat4 parentMatrix);
        private:
        /**
         * Returns the vertex buffer object for this model.
         **/
        virtual int generateVertexBufferObject()=0;
    };
}