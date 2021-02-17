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

Project::Model::Model(glm::mat4 parentMatrix,  glm::vec3 position, float rotation, glm::vec3 scale) {
    _parentMatrix = parentMatrix;
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
  /*  _relativePositions.push_back((model->getPosition() - _position)); */
    _numChildren++;
}

glm::vec3 Project::Model::getPosition() {
    return _position;
}

void Project::Model::setPosition(glm::vec3 position) {
    _position = position;
    _parentMatrix = glm::translate(glm::mat4(1.0f), _position) * glm::rotate(glm::mat4(1.0f), _rotation, glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0f), _scale);
    // used for loop for simplicity/personal time contraint --> change to iterators?
    for (int i = 0; i < _numChildren; i++) {
        // Get relative
        _children[i]->setParentMatrix(_parentMatrix);
    }
}

void Project::Model::setScaling(glm::vec3 scale) {
    _scale = scale;
    _parentMatrix = glm::translate(glm::mat4(1.0f), _position) * glm::rotate(glm::mat4(1.0f), _rotation, glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0f), _scale);
    for (int i = 0; i < _numChildren; i++) {
        // Update the relative
        _children[i]->setParentMatrix(_parentMatrix);
    }
    

    setPosition(_position);
}

glm::vec3 Project::Model::getScale() {
    return _scale;
}

void Project::Model::setTranslation(glm::vec3 translation) {
    _position += translation;


    /*
    for (Project::Model* child : _children) {
        (*child).setTranslation(translation);
    }
    */
}

void Project::Model::setRotation(float rotation) {
    _rotation = rotation;
    _parentMatrix = glm::translate(glm::mat4(1.0f), _position) * glm::rotate(glm::mat4(1.0f), _rotation, glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0f), _scale);
    for (int i = 0; i < _numChildren; i++) {
        // Update the relative
        _children[i]->setParentMatrix(_parentMatrix);
    }
}

float Project::Model::getRotation() {
    return _rotation;
}

glm::mat4 Project::Model::getParentMatrix() {
    return _parentMatrix;
}

void Project::Model::setParentMatrix(glm::mat4 parentMatrix) {
    _parentMatrix = parentMatrix;
}

int Project::Model::getVertexBufferObject() {
    return _vaoRef;
}
void Project::Model::setVertexBufferObject(int vao) {
    _vaoRef = vao;
}