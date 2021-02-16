#pragma once
#include "../contexts/DrawContext.h"

namespace Project {
    /**
    * Camera model
    **/
    class Camera {
    private:
        GLuint _cameraMatrixLocation;
        glm::mat4 _cameraMatrix;
        glm::vec3 _position;
        glm::vec3 _lookAt;
        glm::vec3 _up;

        float _cameraSpeed;
        float _cameraAngularSpeed;
        float _cameraHorizontalAngle;
        float _cameraVerticalAngle;
        double _prevFrameTime;
        double _prevMousePosX;
        double _prevMousePosY;

        float MAX_ZOOM;
        float MIN_ZOOM;
        float fieldOfViewAngle;

    public:
        Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up, GLuint location);
        /**
        * Initialize the camera matrix in default position
        **/
        void setupCamera(Project::DrawContext context);

        void setCameraMatrixLocation(GLuint location);

        /**
        * Adds pan transformation to camera matrix
        * Horitzontal movement in XZ space
        **/
        /*  void panCamera(double dx);*/

          /**
          * Adds tilt transformation to camera matrix
          * Vertical movement in YZ space
          **/
          //void tiltCamera(double dy);

        void calculatePosition(DrawContext context, MouseButtonHandler* handler);
    };
}