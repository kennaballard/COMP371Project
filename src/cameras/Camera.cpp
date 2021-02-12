#pragma once
#include "Camera.h"

/**
 * Camera has two main movements: pan and tilt
 * Either direction
 * Rotate the camera's normal to acheive this
 **/

Project::Camera::Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up) {
	_position = position;
	_lookAt = lookAt;
	_up = up;

    _cameraMatrix = glm::lookAt(_position,  // eye
        _position + _lookAt,  // center
        _up); // up
}


glm::mat4 Project::Camera::setupCamera(DrawContext context) {
    // Set initial view matrix
    return _cameraMatrix;
}

void Project::Camera::panCamera() {
    const float radius = 1.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;

    _cameraMatrix = glm::lookAt(_position,  // eye
        _position + glm::vec3(camX, 0.0f, camZ),  // center
        _up);
    //glUniformMatrix4fv(_cameraMatrixLocation, 1, GL_FALSE, &_cameraMatrix[0][0]);
}

void Project::Camera::tiltCamera() {
    const float radius = 1.0f;
    float camZ = cos(glfwGetTime()) * radius;
    float camY = -sin(glfwGetTime()) * radius;

    _cameraMatrix = glm::lookAt(_position,  // eye
        _position + glm::vec3(0.0f, camY, camZ),  // center
        _up);
    //glUniformMatrix4fv(_cameraMatrixLocation, 1, GL_FALSE, &_cameraMatrix[0][0]);
}