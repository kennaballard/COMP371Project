#include <GLFW/glfw3.h>

/**
 * This is to keep track of the window used to draw models in.
 * 
 **/
class DrawContext {
    public:
    // TODO: keep track of scaling, rotation, translation in a list for each update.
    // TODO: add copy() functionality
    // TODO: add support for DrawContext and drawing children models.
    DrawContext(GLFWwindow* window);

    /**
     * Returns the window from which the drawing should be done on.
     **/
    GLFWwindow* getWindow();
};