#pragma once
#include "./MouseCursorHandler.h"
/**
 * This handles all mouse Cursor events
 **/
Project::MouseCursorHandler::MouseCursorHandler(MouseButtonHandler* mouseButtonHandler, Project::DrawContext context) {
    _mouseButtonHandler = mouseButtonHandler;
    _context = context;
    _xPos = 0;
    _yPos = 0;
}

void Project::MouseCursorHandler::handle(GLFWwindow* window, double xPos, double yPos) {
    // Check what button for drag

    if (_mouseButtonHandler->getLeftPressed()) {
        // zoom
    }
    if (_mouseButtonHandler->getRightPressed()) {
        //// pan drag
        std::cout << "Panning" << std::endl;
        double dx = xPos - _xPos;

    }
    if (_mouseButtonHandler->getMiddlePressed()) {
        //// tilt drag
        //double dy = yPos - _yPos;
        //std::cout << "Tilting" << std::endl;
        //_context.getActiveCamera().tiltCamera(yPos);
    }

    _xPos = xPos;
    _yPos = yPos;
}