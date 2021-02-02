#include "DrawContext.h"

namespace Project {
// TODO: keep track of scaling, rotation, translation in a list for each update.
// TODO: add copy() functionality
// TODO: add support for DrawContext and drawing children models.
DrawContext::DrawContext(GLFWwindow* window) {
    _window = window;
}

/**
 * Returns the window from which the drawing should be done on.
 **/
GLFWwindow* DrawContext::getWindow() {
    return _window;
}
}