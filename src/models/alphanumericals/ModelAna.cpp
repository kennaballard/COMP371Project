#pragma once
#include <iostream>
#include "Model.h"

#include "../models/alphanumericals/ModelA.cpp"
#include "../models/alphanumericals/ModelL.cpp"
#include "../models/alphanumericals/Model4.cpp"
#include "../models/alphanumericals/Model8.cpp"

/**
 * Models each have their own shader program and vertex buffer object.
 * While that is slower than placing them all together, it facilitates
 * drawing several objects that have no relations to each other.
 *
 * Models have child models that will be drawn after the parent model
 * is drawn. Children will keep the .. of the parent model.
 **/
class ModelAna : public Project::Model {
public:
    ModelAna(glm::mat4 parentMatrix, glm::vec3 position, float rotation, glm::vec3 scale) : Project::Model::Model(parentMatrix, position, rotation, scale) {
        glm::mat4 newMatrix = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::scale(glm::mat4(1.0f), scale); 
        
        //ModelAna
        glm::vec3 posA = glm::vec3(-1.5f, 1.0f, 0.04f);
        glm::vec3 posL = glm::vec3(-0.5f, 1.0f, 0.0f);
        glm::vec3 pos4 = glm::vec3(0.5f, 1.0f, 0.0f);
        glm::vec3 pos8 = glm::vec3(1.5f, 1.0f, 0.04f);


        // Add children in parallel to their relative positions
        //ModelAna
        addChild(new ModelA(newMatrix, posA, 0.0785f, glm::vec3(1.0f)));
        addChild(new ModelA(newMatrix, posL, 0.0f, glm::vec3(1.0f)));
        addChild(new Model4(newMatrix, pos4, 0.0f, glm::vec3(1.0f)));
        addChild(new Model8(newMatrix, pos8, -0.0785f, glm::vec3(1.0f)));

    }
protected:
    /**
     * Draws the model with the assumption that the scale is 1:1
     * and the model is "standing" (parallel to the Y-axis).
     **/
    void DrawModel(Project::DrawContext context) {}
public:
    /**
     * Returns the vertex buffer object for this model.
     **/
    int generateVertexBufferObject() {
        return -1;
    }
};