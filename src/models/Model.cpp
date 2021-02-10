#pragma once
#include "Model.h"

/**
 * Models each have their own shader program and buffer object.
 * While that is slower than placing them all together, it facilitates
 * drawing several objects that have no relation to each other.
 * 
 * Models have child models that will be drawn after the parent model
 * is drawn. Children will keep the transformations of the parent model.
 **/

Project::Model::Model(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
    _position = position;
    _rotation = rotation;
    _scale = scale;
}

void Project::Model::draw(DrawContext context) {
    // TODO: apply scale, translate, rotate here
    int shaderProgram = getShaderProgram();
    int vbo = getVertexBufferObject();
    glUseProgram(shaderProgram);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    drawModel(context, shaderProgram, vbo);

    context.push(_position, _rotation, _scale);
    for (Project::Model* child : _children) {
        (*child).draw(context);
    }
    Project::TransformationContext transformations = context.pop();
    // TODO: undo scale (+zoom), rotate, translate.
    // Data in variable transformations.

    glDeleteProgram(shaderProgram);
    //glDeleteBuffers((GLsizei) sizeof(glm::vec3) * 16, (GLuint*) vbo);
}

void Project::Model::rotate(glm::vec3 rotation) {
    _rotation += rotation;
}

void Project::Model::scale(glm::vec3 scale) {
    _scale *= scale;
}

void Project::Model::translate(glm::vec3 translation) {
    _position += translation;
}