#pragma once
#include "./MouseCursorHandler.h"
/**
 * This handles all mouse Cursor events
 **/
Project::MouseCursorHandler::MouseCursorHandler(MouseButtonHandler* mouseButtonHandler) {
    _mouseButtonHandler = mouseButtonHandler;
}

void Project::MouseCursorHandler::handle(GLFWwindow* window, double xPos, double yPos) {
    // Check what button for drag

    if (_mouseButtonHandler->getLeftPressed()) {
        // zoom
    }
    if (_mouseButtonHandler->getRightPressed()) {
        // pan drag
    }
    if (_mouseButtonHandler->getMiddlePressed()) {
        // tilt drag
    }
}