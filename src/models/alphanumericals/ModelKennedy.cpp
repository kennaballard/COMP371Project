#pragma once
#include <iostream>
#include "Model.h"
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
        glm::vec3 posK = glm::vec3(-1.5f,  0.0f, 0.0f);
        glm::vec3 posY = glm::vec3(-0.5f, 0.0f, 0.0f);
        glm::vec3 pos4 = glm::vec3(0.5f, 0.0f, 0.0f);
        glm::vec3 pos0 = glm::vec3(1.5f, 0.0f, 0.0f);

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
     * Returns the vertex buffer object for this model.
     **/
    int generateVertexBufferObject() {
        return -1;
    }
};