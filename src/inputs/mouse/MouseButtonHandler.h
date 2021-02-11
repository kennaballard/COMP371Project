#pragma once

namespace Project {
    class MouseButtonHandler {
    public:
        /**
         * Handles all mouse button input events.
         **/

        virtual void handle(GLFWwindow* window, int button, int action, int mods);
    };
}