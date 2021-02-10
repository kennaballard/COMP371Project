#pragma once
#include <iostream>
#include "Model.h"
#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp>

#include "../models/alphanumericals/Model0.cpp"
#include "../models/alphanumericals/Model4.cpp"
#include "../models/alphanumericals/ModelK.cpp"
#include "../models/alphanumericals/ModelY.cpp"

/**
 * Models each have their own shader program and vertex buffer object.
 * While that is slower than placing them all together, it facilitates
 * drawing several objects that have no relations to each other.
 *
 * Models have child models that will be drawn after the parent model
 * is drawn. Children will keep the .. of the parent model.
 **/
class ModelKennedy : public Project::Model {
public:
    ModelKennedy(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : Project::Model::Model(position, rotation, scale) {
        glm::vec3 posK = glm::vec3(-0.375f, -0.25f, 0);
        glm::vec3 posY = glm::vec3(-0.125f, -0.25f, 0);
        glm::vec3 pos4 = glm::vec3(0.125f, -0.25f, 0);
        glm::vec3 pos0 = glm::vec3(0.375f, -0.25f, 0);

        // Add children in parallel to their relative positions
        addChild(new ModelK(position+posK, rotation, scale));
        addChild(new ModelY(position+posY, rotation, scale));
        addChild(new Model4(position+pos4, rotation, scale));
        addChild(new Model0(position+pos0, rotation, scale));     
    }
protected:
    /**
     * Draws the model with the assumption that the scale is 1:1
     * and the model is "standing" (parallel to the Y-axis).
     **/
    void DrawModel(Project::DrawContext context) {}
public:
    /**
     * Returns the fully compiled shader program for this model.
     **/
    int generateShaderProgram() {
        return -1;
    }

    /**
     * Returns the vertex buffer object for this model.
     **/
    int generateVertexBufferObject() {
        return -1;
    }

private:
    std::vector<glm::vec3> _relativePositions;
    const char* Model::getVertexShaderSource()
    {
        // TODO - Read from a .glsl file instead.
        return
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;"
            "layout (location = 1) in vec3 aColor;"
            "uniform mat4 worldMatrix;"
            "out vec3 vertexColor;"
            "void main()"
            "{"
            "   vertexColor = aColor;"
            "   gl_Position = worldMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);"
            "}";
    }


    const char* Model::getFragmentShaderSource()
    {
        // TODO - Read from a .glsl file instead.
        return
            "#version 330 core\n"
            "in vec3 vertexColor;"
            "out vec4 FragColor;"
            "void main()"
            "{"
            "   FragColor = vec4(1.0, 1.0, 1.0, 1.0f);"
            "}";
    }
};