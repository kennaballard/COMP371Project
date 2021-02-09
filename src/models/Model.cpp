#pragma once
#include "Model.h"

/**
 * Models each have their own shader program and buffer object.
 * While that is slower than placing them all together, it facilitates
 * drawing several objects that have no relation to each other.
 * 
 * Models have child models that will be drawn after the parent model
 * is drawn. Children will keep the .. of the parent model.
 **/

Project::Model::Model(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
    _position = position;
    _rotation = rotation;
    _scale = scale;
    _children = std::vector<Model*>();
}

void Project::Model::Draw(DrawContext context) {
    // TODO: scale (+zoom), translate, rotate
    int shaderProgram = getShaderProgram();
    int vbo = getVertexBufferObject();
    glUseProgram(shaderProgram);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    DrawModel(context);

    for (Project::Model* child : _children) {
        (*child).Draw(context);
    }
    // TODO: undo scale (+zoom), rotate, translate
}

void Project::Model::addChild(Project::Model* model) {
    _children.push_back(model);
}

glm::vec3 Project::Model::getPosition() {
    return _position;
}

void Project::Model::SetScaling(glm::vec3 scale) {
    _scale = scale;

    for (Project::Model* child : _children) {
        (*child).SetScaling(scale);
    }
}

glm::vec3 Project::Model::getScale() {
    return _scale;
}