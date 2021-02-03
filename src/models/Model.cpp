#include "Model.h"
#include "../contexts/DrawContext.cpp"

/**
 * Models each have their own shader program and vertex buffer object.
 * While that is slower than placing them all together, it facilitates
 * drawing several objects that have no relations to each other.
 * 
 * Models have child models that will be drawn after the parent model
 * is drawn. Children will keep the .. of the parent model.
 **/
class Model {
    private:
    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;
    bool _reflectionX;
    bool _reflectionY;
    bool _reflectionZ;

    protected:
    std::vector<Model> _children;
    virtual void Model::DrawModel(DrawContext context);

    public:
    Model::Model(glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 rotation = glm::vec3(0, 0, 0), glm::vec3 scale = glm::vec3(1, 1, 1)) {

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

    virtual int Model::getShaderProgram();
    virtual int Model::getVertexBufferObject();

    void Model::SetScaling(glm::vec3 scale) {
        _scale = scale;
    }
};