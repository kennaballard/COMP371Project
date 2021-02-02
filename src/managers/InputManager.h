#ifndef InputManagerH
#define InputManagerH
#include "../inputs/InputHandler.h"
#include <map>

namespace Project {
/**
 * This handles keyboard and mouse inputs. Any other user input
 * will also be handled through if ever needed.
 * 
 * Each type of input will have its own set of event handlers,
 * such as the keyboard key pressed or mouse key pressed.
 * 
 * Normally, this should be resolved through dependency injection,
 * but due to the size of the project this will be a singleton.
 **/
class InputManager {
    private:
    std::map<int, InputHandler> _keyboard;
    std::map<int, InputHandler> _mouse;

    public:
    InputManager();
    void handleKeyboard(int keyCode);
    void handleMouse(int mouseCode);
};
}
#endif