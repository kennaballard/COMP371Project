#pragma once
#include <iostream>
#include "Model.h"
#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp>

/**
 * Models each have their own shader program and vertex buffer object.
 * While that is slower than placing them all together, it facilitates
 * drawing several objects that have no relations to each other.
 *
 * Models have child models that will be drawn after the parent model
 * is drawn. Children will keep the .. of the parent model.
 **/
class ModelA : public Project::Model {
public:
    ModelA(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : Project::Model::Model(position, rotation, scale) {
        setVertexBufferObject(generateVertexBufferObject());
    }

protected:
    /**
     * Draws the model with the assumption that the scale is 1:1
     * and the model is "standing" (parallel to the Y-axis).
     **/
     // Stretches cube into a rectangle given params
    glm::mat4 partTranslationMatrix(GLfloat posX, GLfloat posY, GLfloat posZ) {
        return glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, posZ));
    }

    glm::mat4 partScalingMatrix(GLfloat widthScale, GLfloat heightScale, GLfloat depthScale) {
        return glm::scale(glm::mat4(1.0f), glm::vec3(widthScale, heightScale, depthScale));
    }

    void DrawModel(Project::DrawContext context) {
       
        int shader = context.getShaderProgram();

        //////////////////////////////////
        //                               //
        //     building cubes for "A"    //
        //////////////////////////////////


       //left cube
        glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.125f, 1.0f, 0.125f));
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.8f, 0.0f, 0.0f));

        glm::mat4 worldMatrix = translationMatrix * scalingMatrix;
        GLuint worldMatrixLocation = glGetUniformLocation(shader, "worldMatrix");
        glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //middle cube
        scalingMatrix = scale(glm::mat4(1.0f), glm::vec3(0.125f, 0.125f, 0.125f));
        translationMatrix = translate(glm::mat4(1.0f), glm::vec3(-0.65f, 0.0f, 0.0f));

        worldMatrix = translationMatrix * scalingMatrix;
        worldMatrixLocation = glGetUniformLocation(shader, "worldMatrix");
        glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        //top cube
        scalingMatrix = scale(glm::mat4(1.0f), glm::vec3(0.125f, 0.125f, 0.125f));
        translationMatrix = translate(glm::mat4(1.0f), glm::vec3(-0.65f, 0.44f, 0.0f));

        worldMatrix = translationMatrix * scalingMatrix;
        worldMatrixLocation = glGetUniformLocation(shader, "worldMatrix");
        glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //right cube
        scalingMatrix = scale(glm::mat4(1.0f), glm::vec3(0.125f, 1.0f, 0.125f));
        translationMatrix = translate(glm::mat4(1.0f), glm::vec3(-0.50f, 0.0f, 0.0f));

        worldMatrix = translationMatrix * scalingMatrix;
        worldMatrixLocation = glGetUniformLocation(shader, "worldMatrix");
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


            //front
            glm::vec3(-0.5f,-0.5f, 0.5f),
            glm::vec3(1.0, 0.0, 0.0),
            glm::vec3(0.5f,-0.5f, 0.5f),
            glm::vec3(0.0, 1.0, 0.0),
            glm::vec3(0.5f, 0.5f, 0.5f),
            glm::vec3(0.0, 0.0, 1.0),
            glm::vec3(-0.5f, 0.5f, 0.5f),
            glm::vec3(1.0, 1.0, 1.0),


            //back
            glm::vec3(-0.5f,-0.5f, -0.5f),
            glm::vec3(1.0, 0.0, 0.0),
            glm::vec3(0.5f,-0.5f, -0.5f),
            glm::vec3(0.0, 1.0, 0.0),
            glm::vec3(0.5f, 0.5f, -0.5f),
            glm::vec3(0.0, 0.0, 1.0),
            glm::vec3(-0.5f, 0.5f, -0.5f),
            glm::vec3(1.0, 1.0, 1.0)

        };

        GLuint cube_elements[] = {

            //////////////////
            //  a  cube    //
            /////////////////

                 //front
                 0, 1, 2,
                 2, 3, 0,
                 // right
                 1, 5, 6,
                 6, 2, 1,
                 // back
                 7, 6, 5,
                 5, 4, 7,
                 // left
                 4, 0, 3,
                 3, 7, 4,
                 // bottom
                 4, 5, 1,
                 1, 0, 4,
                 // top
                 3, 2, 6,
                 6, 7, 3,

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
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);

        glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
            3,                   // size
            GL_FLOAT,            // type
            GL_FALSE,            // normalized?
            2 * sizeof(glm::vec3), // stride - each vertex contain 2 vec3 (position, color)
            (void*)0             // array buffer offset
        );
        glEnableVertexAttribArray(0);


        glVertexAttribPointer(1,                            // attribute 1 matches aColor in Vertex Shader
            3,
            GL_FLOAT,
            GL_FALSE,
            2 * sizeof(glm::vec3),
            (void*)sizeof(glm::vec3)      // color is offseted a vec3 (comes after position)
        );
        glEnableVertexAttribArray(1);
       
     /*   glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
*/

        return vertexBufferObject;
    }
};