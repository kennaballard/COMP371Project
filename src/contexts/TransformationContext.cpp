#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Project {
    struct TransformationContext {
        private:
        glm::vec3 _translation;
        glm::vec3 _rotation;
        glm::vec3 _scale;

        public:
        TransformationContext(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale) {
            _translation = translation;
            _rotation = rotation;
            _scale = scale;
        }

        glm::vec3 getTranslation() {
            return _translation;
        }

        glm::vec3 getRotation() {
            return _rotation;
        }

        glm::vec3 getScale() {
            return _scale;
        }
    };
}