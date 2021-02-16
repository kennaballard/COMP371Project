#pragma once
#include "Camera.h"
#include "mouse/MouseButtonHandler.h"
/**
 * Camera has two main movements: pan and tilt
 * Either direction
 * Rotate the camera's normal to acheive this
 **/

Project::Camera::Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up, GLuint location) {
	_position = _defaultPosition = position;
	_lookAt = _defaultLookAt = lookAt;
	_up = _defaultUp = up;
    _cameraMatrixLocation = location;
    _cameraMatrix = glm::lookAt(_position,  // eye
        _position + _lookAt,  // center
        _up); // up

    _cameraAngularSpeed = 1.0f;
    _cameraSpeed = 1.0f;
    _cameraHorizontalAngle = 90.0f;
    _cameraVerticalAngle = 0.0f;
    _prevFrameTime = glfwGetTime();
    _prevMousePosX = 0;
    _prevMousePosY = 0;

    MAX_ZOOM = 45.0f;
    MIN_ZOOM = 1.0f;
    fieldOfViewAngle = 45.0f;
}


void Project::Camera::setupCamera(DrawContext context) {
    glUniformMatrix4fv(_cameraMatrixLocation, 1, GL_FALSE, &_cameraMatrix[0][0]);
    // Set initial view matrix
    glfwGetCursorPos(context.getWindow(), &_prevMousePosX, &_prevMousePosY);
}

void Project::Camera::setCameraMatrixLocation(GLuint location) {
    _cameraMatrixLocation = location;
}

void Project::Camera::resetPosition() {
    _position = _defaultPosition;
    _lookAt = _defaultLookAt;
    _up = _defaultUp;

    _cameraHorizontalAngle = 90.0f;
    _cameraVerticalAngle = 0.0f;
}

void Project::Camera::calculatePosition(Project::DrawContext context, Project::MouseButtonHandler* handler) {
    float dt = glfwGetTime() - _prevFrameTime;
    _prevFrameTime += dt;

    // Current Mouse Positions
    double mousePosX, mousePosY;
    glfwGetCursorPos(context.getWindow(), &mousePosX, &mousePosY);

    // Change in pos
    double dx = mousePosX - _prevMousePosX;
    double dy = mousePosY - _prevMousePosY;

    // Update Prev
    _prevMousePosX = mousePosX;
    _prevMousePosY = mousePosY;

    // Convert to spherical coordinates
    const float cameraAngularSpeed = 60.0f;
    
    // Only pan and tilt on button press
    if (handler->getMiddlePressed()) {
        // Tilt
        _cameraVerticalAngle -= dy * cameraAngularSpeed * dt;
    }
    if (handler->getRightPressed()) {
        // Pan
        _cameraHorizontalAngle -= dx * cameraAngularSpeed * dt;
    }

    // Clamp vertical angle to [-85, 85] degrees
    _cameraVerticalAngle = std::max(-85.0f, std::min(85.0f, _cameraVerticalAngle));

    float theta = glm::radians(_cameraHorizontalAngle);
    float phi = glm::radians(_cameraVerticalAngle);

    _lookAt = glm::vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));
    glm::vec3 cameraSideVector = glm::cross(_lookAt, glm::vec3(0.0f, 1.0f, 0.0f));

    glm::normalize(cameraSideVector);

    _cameraMatrix = glm::lookAt(_position, _position + _lookAt, _up);
    glUniformMatrix4fv(_cameraMatrixLocation, 1, GL_FALSE, &_cameraMatrix[0][0]);
}