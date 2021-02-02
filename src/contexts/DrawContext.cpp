#include "DrawContext.h"

class DrawContext {
    private:
    GLFWwindow* _window;

    public:
    // TODO: keep track of scaling, rotation, translation in a list for each update.
    // TODO: add copy() functionality
    // TODO: add support for DrawContext and drawing children models.
    DrawContext(GLFWwindow* window) {
        _window = window;
    }

    public:
    /**
     * Returns the window from which the drawing should be done on.
     **/
    GLFWwindow* DrawContext::getWindow() {
        return _window;
    }
};