#pragma once
#include <iostream>
#include "Model.h"

/**
 * Models each have their own shader program and vertex buffer object.
 * While that is slower than placing them all together, it facilitates
 * drawing several objects that have no relations to each other.
 * 
 * Models have child models that will be drawn after the parent model
 * is drawn. Children will keep the .. of the parent model.
 **/
class ModelT : public Project::Model {
    public:
    ModelT(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : Project::Model::Model(position, rotation, scale) { }

    protected:
    /**
     * Draws the model with the assumption that the scale is 1:1
     * and the model is "standing" (parallel to the Y-axis).
     **/
    void DrawModel(Project::DrawContext context) {
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    public:
    /**
     * Returns the vertex buffer object for this model.
     **/
    int getVertexBufferObject() {
        // A vertex is a point on a polygon, it contains positions and other data (eg: colors)
        glm::vec3 vertexArray[] = {
            glm::vec3( 0.0f,  0.5f, 0.0f),  // top center position
            glm::vec3( 1.0f,  0.0f, 0.0f),  // top center color (red)
            glm::vec3( 0.5f, -0.5f, 0.0f),  // bottom right
            glm::vec3( 0.0f,  1.0f, 0.0f),  // bottom right color (green)
            glm::vec3(-0.5f, -0.5f, 0.0f),  // bottom left
            glm::vec3( 0.0f,  0.0f, 1.0f),  // bottom left color (blue)
        };
        
        // Create a vertex array
        GLuint vertexArrayObject;
        glGenVertexArrays(1, &vertexArrayObject);
        glBindVertexArray(vertexArrayObject);
        
        
        // Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
        GLuint vertexBufferObject;
        glGenBuffers(1, &vertexBufferObject);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
                            3,                   // size
                            GL_FLOAT,            // type
                            GL_FALSE,            // normalized?
                            2 * sizeof(glm::vec3), // stride - each vertex contain 2 vec3 (position, color)
                            (void*) 0             // array buffer offset
                            );
        glEnableVertexAttribArray(0);
        
        
        glVertexAttribPointer(1,                            // attribute 1 matches aColor in Vertex Shader
                            3,
                            GL_FLOAT,
                            GL_FALSE,
                            2*sizeof(glm::vec3),
                            (void*)sizeof(glm::vec3)      // color is offseted a vec3 (comes after position)
                            );
        glEnableVertexAttribArray(1);
        
        
        return vertexBufferObject;
    }
};