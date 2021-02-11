#include "../MouseButtonHandler.cpp"

/**
 * This handles the eight mouse button click.
 * This code will be executed whenever the button is clicker
 * Tracks mouse movement to determine action
 *
 * TODO: Implement tracking/action
 **/
class RightButtonHandler : public Project::MouseButtonHandler {
private:
    bool _isPressed = false;
public:

    virtual void Project::InputHandler::handle(int action) {
        // Input code here.
        // Mouse movement in X direction to pan
        if (action == GLFW_PRESS) {
            std::cout << "Right Press" << std::endl;
            _isPressed = true;
        }
        else if (action == GLFW_RELEASE) {
            std::cout << "Right Lift" << std::endl;
            _isPressed = false;
        }
    }

    bool getIsPressed() {
        return _isPressed;
    }
};