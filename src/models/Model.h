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
        glm::vec3 _position;
        glm::vec3 _rotation;
        glm::vec3 _scale;
        bool _reflectionX;
        bool _reflectionY;
        bool _reflectionZ;
        std::vector<Model*> _children;
        std::vector<glm::vec3> _relativePositions;
        int _numChildren;
        int _vboRef;

        protected:
        /**
         * Draws the model with the assumption that the scale is 1:1
         * and the model is "standing" (parallel to the Y-axis).
         **/
        virtual void DrawModel(Project::DrawContext context)=0;

        public:
        Model(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

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
        void setRotation(glm::vec3 rotation);

        private:
        /**
         * Returns the vertex buffer object for this model.
         **/
        virtual int generateVertexBufferObject()=0;
    };
}