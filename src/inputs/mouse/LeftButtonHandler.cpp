#include "../MouseButtonHandler.cpp"

/**
 * This handles the left mouse button press.
 * This code will be executed whenever the button is pressed.
 *
 * TODO: Track movement to determine action 
 **/
class LeftButtonHandler : public Project::MouseButtonHandler {
private:
    bool _isPressed = false;
public:

    virtual void Project::MouseButtonHandler::handle(GLFWwindow* window, int button, int action, int mods) {
        // Input code here.
        // Mouse movement in X direction to pan
        if (action == GLFW_PRESS) {
            std::cout << "left Press" << std::endl;
            _isPressed = true;
        }
        else if (action == GLFW_RELEASE) {
            std::cout << "left Lift" << std::endl;
            _isPressed = false;
        }
    }

    bool getIsPressed() {
        return _isPressed;
    }
};