#pragma once
#include "MouseButtonHandler.h"

namespace Project {
    class MouseCursorHandler {
    private:
        MouseButtonHandler* _mouseButtonHandler;
    public:
        MouseCursorHandler(MouseButtonHandler* mouseButtonHandler);
        /**
         * Handles all mouse button input events.
         **/
        void handle(GLFWwindow* window, double xPos, double yPos);
    };
}