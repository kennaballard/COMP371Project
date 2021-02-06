#include "DrawContext.h"

// TODO: keep track of scaling, rotation, translation in a list for each update.
// TODO: add copy() functionality
// TODO: add support for DrawContext and drawing children models.
Project::DrawContext::DrawContext(GLFWwindow* window) {
    _window = window;
}

/**
 * Returns the window from which the drawing should be done on.
 **/
GLFWwindow* Project::DrawContext::getWindow() {
    return _window;
}