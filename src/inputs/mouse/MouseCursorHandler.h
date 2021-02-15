#pragma once
#include "MouseButtonHandler.h"

namespace Project {
    class MouseCursorHandler {
    private:
        double _xPos;
        double _yPos;
        Project::DrawContext _context;
        MouseButtonHandler* _mouseButtonHandler;
    public:
        MouseCursorHandler(MouseButtonHandler* mouseButtonHandler, Project::DrawContext context);
        /**
         * Handles all mouse button input events.
         **/
        void handle(GLFWwindow* window, double xPos, double yPos);
    };
}