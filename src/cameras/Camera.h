#pragma once
#include "../contexts/DrawContext.h"

namespace Project {
    /**
    * Camera model
    **/
    class Camera {
    private:
        glm::mat4 _cameraMatrix;
        glm::vec3 _position;
        glm::vec3 _lookAt;
        glm::vec3 _up;

    public:
        Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up);
        /**
        * Initialize the camera matrix in default position
        **/
        glm::mat4 setupCamera(DrawContext context);

        /**
        * Adds pan transformation to camera matrix
        * Horitzontal movement in XZ space
        **/
        void panCamera();

        /**
        * Adds tilt transformation to camera matrix
        * Vertical movement in YZ space
        **/
        void tiltCamera();
    };
}