#include "../Model.cpp"

/**
 * This model is for the letter S.
 * 
 * Models each have their own shader program and vertex buffer object.
 * While that is slower than placing them all together, it facilitates
 * drawing several objects that have no relations to each other.
 * 
 * Models have child models that will be drawn after the parent model
 * is drawn. Children will keep the .. of the parent model.
 **/
class ModelS : public Model {
    protected:
    virtual void DrawModel() {
        
    }

    virtual int getShaderProgram() {
        return -1;
    }

    virtual int getVertexBufferObject() {
        return -1;
    }
};