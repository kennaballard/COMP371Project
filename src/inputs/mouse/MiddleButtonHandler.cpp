#include "../MouseButtonHandler.cpp"

/**
 * This handles the middle mouse button click.
 * This code will be executed whenever the button is pressed.
 * Tracks mouse movement to determine action
 *
 * TODO: Track Y-direction movement to tilt
 **/
class MiddleButtonHandler : public Project::MouseButtonHandler {
private:
    bool _isPressed = false;
public:

    virtual void Project::InputHandler::handle(int action) {
        // Input code here.
        // Mouse movement in X direction to pan
        if (action == GLFW_PRESS) {
            std::cout << "Middle Press" << std::endl;
            _isPressed = true;
        }
        else if (action == GLFW_RELEASE) {
            std::cout << "middle Lift" << std::endl;
            _isPressed = false;
        }
    }

    bool getIsPressed() {
        return _isPressed;
    }
};