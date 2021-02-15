#pragma once
#include "../contexts/DrawContext.h"

namespace Project {
    class MouseButtonHandler {
    private:
        Project::DrawContext _context;

        bool _rightPressed;
        bool _leftPressed;
        bool _middlePressed;

        bool setIsPressed(int action);
    public:
        MouseButtonHandler(Project::DrawContext context);
        /**
         * Handles all mouse button input events.
         **/
        void handle(GLFWwindow* window, int button, int action, int mods);

        bool getRightPressed();
        bool getLeftPressed();
        bool getMiddlePressed();
    };
}