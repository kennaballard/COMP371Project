#include "./MouseButtonHandler.h"
/**
 * This handles all mouse events
 * This code will be executed whenever a button is pressed.
 * Calls appropriate handler
 **/
class MouseButtonHandler {
public:
    virtual void MouseButtonHandler::handle(GLFWwindow* window, int button, int action, int mods) {
        if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            rightButtonHandler.handle(action);
        }

        if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
            middleButtonHandler.handle(action);
        }

        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            leftButtonHandler.handle(action);
        }
    }

    void leftButtonPressed
};