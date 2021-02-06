#include "../inputs/InputHandler.h"
#include <map>

Project::InputManager::InputManager() {
    
}

void Project::InputManager::handleKeyboard(int keyCode) {
    auto search = _keyboard.find(keyCode);
    if (search == _keyboard.end())
        return;

    (*(search->second)).handle();
}

void Project::InputManager::handleMouse(int mouseCode) {
    auto search = _mouse.find(mouseCode);
    if (search == _mouse.end())
        return;

    (*(search->second)).handle();
}