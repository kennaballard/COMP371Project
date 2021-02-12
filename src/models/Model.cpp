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
    _relativePositions = std::vector<glm::vec3>();
    _numChildren = 0;
}

void Project::Model::Draw(DrawContext context) {
    // TODO: scale (+zoom), translate, rotate
    int shaderProgram = context.getShaderProgram();
    int vao = getVertexBufferObject();
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    DrawModel(context);

    for (Project::Model* child : _children) {
        (*child).Draw(context);
    }
    // TODO: undo scale (+zoom), rotate, translate
}

void Project::Model::addChild(Project::Model* model) {
    _children.push_back(model);

    // Relative position calculation
    _relativePositions.push_back((model->getPosition() - _position));
    _numChildren++;
}

glm::vec3 Project::Model::getPosition() {
    return _position*_scale;
}

void Project::Model::setPosition(glm::vec3 position) {
    _position = position;

    // used for loop for simplicity/personal time contraint --> change to iterators?
    for (int i = 0; i < _numChildren; i++) {
        // Get relative
        _children[i]->setPosition(position+_relativePositions[i]);
    }
}

void Project::Model::setScaling(glm::vec3 scale) {
    _scale = scale;

    for (Project::Model* child : _children) {
        (*child).setScaling(scale);
    }
}

glm::vec3 Project::Model::getScale() {
    return _scale;
}

void Project::Model::setTranslation(glm::vec3 translation) {
    _position += translation;

    for (Project::Model* child : _children) {
        (*child).setTranslation(translation);
    }
}

void Project::Model::setRotation(glm::vec3 rotation) {
    // TODO
    // Not implemeted
    for (Project::Model* child : _children) {
        (*child).setRotation(rotation);
    }
}

int Project::Model::getVertexBufferObject() {
    return _vaoRef;
}
void Project::Model::setVertexBufferObject(int vao) {
    _vaoRef = vao;
}