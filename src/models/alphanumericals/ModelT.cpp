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
    ModelT(glm::mat4 parentMatrix, glm::vec3 position, float rotation, glm::vec3 scale) : Project::Model::Model(parentMatrix, position, rotation, scale) {
        setVertexBufferObject(generateVertexBufferObject());
    }

protected:
    glm::mat4 partTranslationMatrix(GLfloat posX, GLfloat posY, GLfloat posZ) {
        return glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, posZ));
    }

    glm::mat4 partScalingMatrix(GLfloat widthScale, GLfloat heightScale, GLfloat depthScale) {
        return glm::scale(glm::mat4(1.0f), glm::vec3(widthScale, heightScale, depthScale));
    }

    /**
     * Draws the model with the assumption that the scale is 1:1
     * and the model is "standing" (parallel to the Y-axis).
     **/
    void DrawModel(Project::DrawContext context) {
        int shader = context.getShaderProgram();

        GLuint worldMatrixLocation = glGetUniformLocation(shader, "worldMatrix");
        glm::mat4 groupTranslationMatrix = glm::translate(glm::mat4(1.0f), getPosition());
        glm::mat4 groupScaleMatrix = glm::scale(glm::mat4(1.0f), getScale());
        glm::mat4 groupRotationMatrix = glm::rotate(glm::mat4(1.0f), getRotation(), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 parentMatrix = getParentMatrix();
        glm::mat4 groupMatrix = groupTranslationMatrix * groupRotationMatrix * groupScaleMatrix;
        groupMatrix = parentMatrix * groupMatrix;
        glm::mat4 worldMatrix;

        // Top
        worldMatrix = groupMatrix * partTranslationMatrix(0.0f, 0.75f, 0.0f) * partScalingMatrix(0.5f, 0.125f, 0.125f);
        glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // Bottom
        worldMatrix = groupMatrix * partTranslationMatrix(0.0f, -0.125f, 0.0f)  * partScalingMatrix(0.125f, 0.75f, 0.125f);
        glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

public:
    /**
     * Returns the vertex buffer object for this model.
     **/
    int generateVertexBufferObject() {
        // A vertex is a point on a polygon, it contains positions and other data (eg: colors)
        glm::vec3 vertexArray[] = {
            // Front face
            glm::vec3(1.0f,  1.0f, 0.0f),  // top right front
            glm::vec3(1.0f,  0.0f, 0.0f),  // top right color (red)
            glm::vec3(1.0f, -1.0f, 0.0f),  // bottom right front
            glm::vec3(0.0f,  1.0f, 0.0f),  // bottom right color (green)
            glm::vec3(-1.0f, -1.0f, 0.0f),  // bottom left front
            glm::vec3(0.0f,  0.0f, 1.0f),  // bottom left color (blue)
            glm::vec3(-1.0f,  1.0f, 0.0f),  // top left front
            glm::vec3(0.0f,  0.0f, 1.0f),  // top left color (red)
            // Back face
            glm::vec3(1.0f,  1.0f, -1.0f),  // top right back
            glm::vec3(1.0f,  0.0f, 0.0f),  // top right color (red)
            glm::vec3(1.0f, -1.0f, -1.0f),  // bottom right back
            glm::vec3(0.0f,  1.0f, 0.0f),  // bottom right color (green)
            glm::vec3(-1.0f, -1.0f, -1.0f),  // bottom left back
            glm::vec3(0.0f,  1.0f, 0.0f),  // bottom left color (blue)
            glm::vec3(-1.0f,  1.0f, -1.0f),  // top left back
            glm::vec3(0.0f,  0.0f, 1.0f),  // top left color (red)
        };

        unsigned int indices[] = {
            // Left Front
            0, 1, 2,
            0, 2, 3,
            // Right Front
            4, 5, 1,
            4, 1, 0,
            // Top
            4, 0, 3,
            4, 3, 7,
            // Bottom
            5, 1, 2,
            5, 2, 6,
            // Left Back
            3, 2, 6,
            3, 6, 7,
            // Right Back
            7, 6, 5,
            7, 4, 5
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

        GLuint elementBufferObject;
        glGenBuffers(1, &elementBufferObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(
            0,                   // attribute 0 matches aPos in Vertex Shader
            3,                   // size
            GL_FLOAT,            // type
            GL_FALSE,            // normalized?
            2 * sizeof(glm::vec3), // stride - each vertex contain 2 vec3 (position, color)
            (void*)0             // array buffer offset
        );
        glEnableVertexAttribArray(0);


        glVertexAttribPointer(
            1,                            // attribute 1 matches aColor in Vertex Shader
            3,
            GL_FLOAT,
            GL_FALSE,
            2 * sizeof(glm::vec3),
            (void*)sizeof(glm::vec3)      // color is offseted a vec3 (comes after position)
        );
        glEnableVertexAttribArray(1);
       
        return vertexArrayObject;
    }
};