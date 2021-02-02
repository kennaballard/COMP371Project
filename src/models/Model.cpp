#include "Model.h"

/**
 * Models each have their own shader program and vertex buffer object.
 * While that is slower than placing them all together, it facilitates
 * drawing several objects that have no relations to each other.
 * 
 * Models have child models that will be drawn after the parent model
 * is drawn. Children will keep the .. of the parent model.
 **/

namespace Project {
Model::Model(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {

}

void Model::Draw(DrawContext context) {
    // TODO: scale (+zoom), translate, rotate
    int shaderProgram = getShaderProgram();
    int vbo = getVertexBufferObject();
    glUseProgram(shaderProgram);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    DrawModel(context);

    for (Model child : _children) {
        child.Draw(context);
    }
    // TODO: undo scale (+zoom), rotate, translate
}

void Model::SetScaling(glm::vec3 scale) {
    _scale = scale;
}
}