#include "../Model.cpp"
#include <iostream>

namespace Project {
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
class Lab01Model : public Model {
    protected:
    virtual void DrawModel() {
        int vao = getVertexBufferObject();
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
        };

        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    }

    virtual int getShaderProgram() {
        const char *vertexShaderSource = getVertexShaderSource();
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        int success;
        char log[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, log);
            std::cout << "ERROR - Shader - Vertex - Compiled Failed:\n" << log << std::endl;
            return -1;
        }

        const char *fragmentShaderSource = getFragmentShaderSource();
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, log);
            std::cout << "ERROR - Shader - Fragment - Compiled Failed:\n" << log << std::endl;
            return -1;
        }

        unsigned int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, log);
            std::cout << "ERROR - Shader - Program - Compiled Failed:\n" << log << std::endl;
            return -1;
        }

        glUseProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return shaderProgram;
    }

    virtual int getVertexBufferObject() {
        // A vertex is a point on a polygon, it contains positions and other data (eg: colors)
        glm::vec3 vertexArray[] = {
            glm::vec3( 0.0f,  0.5f, 0.0f),  // top center position
            glm::vec3( 1.0f,  0.0f, 0.0f),  // top center color (red)
            glm::vec3( 0.5f, -0.5f, 0.0f),  // bottom right
            glm::vec3( 0.0f,  1.0f, 0.0f),  // bottom right color (green)
            glm::vec3(-0.5f, -0.5f, 0.0f),  // bottom left
            glm::vec3( 0.0f,  0.0f, 1.0f),  // bottom left color (blue)
        };
        
        // Create a vertex array
        GLuint vertexArrayObject;
        glGenVertexArrays(1, &vertexArrayObject);
        glBindVertexArray(vertexArrayObject);
        
        
        // Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
        GLuint vertexBufferObject;
        glGenBuffers(1, &vertexBufferObject);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
                              3,                   // size
                              GL_FLOAT,            // type
                              GL_FALSE,            // normalized?
                              2 * sizeof(glm::vec3), // stride - each vertex contain 2 vec3 (position, color)
                              (void*) 0             // array buffer offset
                            );
        glEnableVertexAttribArray(0);
        
        
        glVertexAttribPointer(1,                            // attribute 1 matches aColor in Vertex Shader
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              2*sizeof(glm::vec3),
                              (void*)sizeof(glm::vec3)      // color is offseted a vec3 (comes after position)
                            );
        glEnableVertexAttribArray(1);
        
        
        return vertexBufferObject;
    }

private:
    const char* Model::getVertexShaderSource()
    {
        // TODO - Insert Vertex Shaders here ...
        // For now, you use a string for your shader code, in the assignment, shaders will be stored in .glsl files
        return
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;"
        "layout (location = 1) in vec3 aColor;"
        "out vec3 vertexColor;"
        "void main()"
        "{"
        "   vertexColor = aColor;"
        "   gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0);"
        "}";
    }


    const char* Model::getFragmentShaderSource()
    {
        // TODO - Insert Fragment Shaders here ...
        return
        "#version 330 core\n"
        "in vec3 vertexColor;"
        "out vec4 FragColor;"
        "void main()"
        "{"
        "   FragColor = vec4(1.0, 1.0, 1.0, 1.0f);"
        "}";
    }
};
}