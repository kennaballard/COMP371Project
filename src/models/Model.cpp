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
    _hirachicalPosition = position;
    _rotation = glm::vec3(1.0f);
    _scale = scale;
    _angle = 1.0f;
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
    return _position;
}

glm::vec3 Project::Model::getHireachicalPosition(){
    return _hirachicalPosition;
}


void Project::Model::setPosition(glm::vec3 position) {
    _position = position;

    // used for loop for simplicity/personal time contraint --> change to iterators?
    for (int i = 0; i < _numChildren; i++) {
        // Get relative
        _children[i]->setPosition(position+(_relativePositions[i]*_scale));
    }
}

void Project::Model::setScaling(glm::vec3 scale) {
    _scale = scale;
   
    for (int i = 0; i < _numChildren; i++) {
        // Update the relative
        _children[i]->setScaling(scale);
    }

    setPosition(_position);
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

glm::vec3 Project::Model::getRotation() {
    return _rotation;
}

//Rotation of the model by a given deegres (angles) around a specific axis.  
void Project::Model::setRotation(glm::vec3 rotationAxis, float angle) {


    _rotation = rotationAxis;
    _angle = _angle + angle;

    for (Project::Model* child : _children) {
        (*child).setRotation(rotationAxis, angle);
    }
}

//Smooth rotation of the model around a specific axis  
void Project::Model::setRotation(glm::vec3 rotationAxis, float rotationalSpeed, float dt) {

    _rotation = rotationAxis;
    _angle = _angle + rotationalSpeed * dt;

    for (Project::Model* child : _children) {
        (*child).setRotation(rotationAxis, rotationalSpeed, dt);

    }
}

float Project::Model::getAngle()
{
    return _angle;
}

int Project::Model::getVertexBufferObject() {
    return _vaoRef;
}
void Project::Model::setVertexBufferObject(int vao) {
    _vaoRef = vao;
}