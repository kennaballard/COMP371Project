#pragma once
#include <iostream>
#include "Model.h"
#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp>



class Floor : public Project::Model {

public:
    
    //Creates floor object for model manager, takes float input as a size for the grid in x/y/z coordinates

    Floor(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : Project::Model::Model(position, rotation, scale) {
        setVertexBufferObject(createFloorArrayObject(0.35f));

    }


    void DrawModel(Project::DrawContext context) {

        int shader = context.getShaderProgram();
        GLuint worldMatrixLocation = glGetUniformLocation(shader, "worldMatrix");
        glm::mat4 floorMatrix = glm::mat4(1.0f);
        glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &floorMatrix[0][0]);
        for (int i = 0; i < 722; i += 2)
            glDrawArrays(GL_LINE_LOOP, i, 2);
    }
private:
    int createFloorArrayObject(float coord)
    {
        // A vertex is a point on a polygon, it contains positions and other data (eg: colors)
        glm::vec3 vertexArray[1444];
        for (int i = 0; i < 516; i += 4) {
            vertexArray[i] = glm::vec3(-64 * coord + (i / 4) * coord, -0.01f, -64 * coord);
            vertexArray[(i + 1)] = glm::vec3(0.5f, 0.5f, 0.0f);
            vertexArray[(i + 2)] = glm::vec3(-64 * coord + (i / 4) * coord, -0.01f, 64 * coord) ;
            vertexArray[(i + 3)] = glm::vec3(0.5f, 0.5f, 0.0f);
            vertexArray[(i + 516)] = glm::vec3(-64 * coord, -0.01f, -64 * coord + (i / 4) * coord );
            vertexArray[(i + 517)] = glm::vec3(0.5f, 0.5f, 0.0f);
            vertexArray[(i + 518)] = glm::vec3(64 * coord, -0.01f, -64 * coord + (i / 4) * coord );
            vertexArray[(i + 519)] = glm::vec3(0.5f, 0.5f, 0.0f);
        }
        vertexArray[1032] = glm::vec3(0.0f, 0.0f, 0.0f);
        vertexArray[1033] = glm::vec3(0.0f, 1.0f, 0.0f);
        vertexArray[1034] = glm::vec3(0.0f , 7 * coord, 0.0f);
        vertexArray[1035] = glm::vec3(0.0f, 1.0f, 0.0f);
        vertexArray[1036] = glm::vec3( 0.0f, 0.0f, 0.0f);
        vertexArray[1037] = glm::vec3(1.0f, 0.0f, 0.0f);
        vertexArray[1038] = glm::vec3(7*coord, 0.0f, 0.0f);
        vertexArray[1039] = glm::vec3(1.0f, 0.0f, 0.0f);
        vertexArray[1040] = glm::vec3(0.0f, 0.0f, 0.0f);
        vertexArray[1041] = glm::vec3(0.0f, 0.0f, 1.0f);
        vertexArray[1042] = glm::vec3(0.0f, 0.0f, 7 * coord);
        vertexArray[1043] = glm::vec3(0.0f, 0.0f, 1.0f);
        vertexArray[1044] = glm::vec3(64 * coord , 0.0f, 0.0f);
        vertexArray[1045] = glm::vec3(1.0f, 0.0f, 0.0f);
        for (int i = 4; i < 400; i += 4) {
            vertexArray[1042 + i] = glm::vec3(64 * coord * cos(2 * 3.1415f * i / 400), 0.0f, 64 * coord * sin(2 * 3.1415f * i / 400));
            vertexArray[1043 + i] = glm::vec3(1.0f, 0.0f, 0.0f);
            vertexArray[1044 + i] = glm::vec3(64 * coord * cos(2 * 3.1415f * i / 400), 0.0f, 64 * coord * sin(2 * 3.1415f * i / 400));
            vertexArray[1045 + i] = glm::vec3(1.0f, 0.0f, 0.0f);
        }
        vertexArray[1442] = glm::vec3(64 * coord, 0.0f, 0.0f);
        vertexArray[1443] = glm::vec3(1.0f, 0.0f, 0.0f);

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

        /* glBindBuffer(GL_ARRAY_BUFFER, 0);
         glBindVertexArray(0);
     */
        return vertexArrayObject;
    }


public:
    /**
     * Returns the vertex buffer object for this model.
     **/
    int generateVertexBufferObject() {
        return -1;
    }
};
    
