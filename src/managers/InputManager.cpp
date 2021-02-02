#include "InputManager.h"

    
namespace Project {
InputManager::InputManager() {
    
}

void InputManager::handleKeyboard(int keyCode) {
    auto search = _keyboard.find(keyCode);
    if (search == _keyboard.end())
        return;

    search->second.handle();
}

void InputManager::handleMouse(int mouseCode) {
    auto search = _mouse.find(mouseCode);
    if (search == _mouse.end())
        return;

    search->second.handle();
}
}