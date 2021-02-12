#pragma once

namespace Project {
    class MouseButtonHandler {
    private:
        bool _rightPressed;
        bool _leftPressed;
        bool _middlePressed;

        bool setIsPressed(int action);
    public:
        MouseButtonHandler();
        /**
         * Handles all mouse button input events.
         **/
        void handle(GLFWwindow* window, int button, int action, int mods);

        bool getRightPressed();
        bool getLeftPressed();
        bool getMiddlePressed();
    };
}