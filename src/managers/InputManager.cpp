#include "../inputs/InputHandler.h"
#include <map>

class InputManager {
    private:
    static InputManager* _instance;
    std::map<int, InputHandler> _keyboard;
    std::map<int, InputHandler> _mouse;

    InputManager::InputManager() {
        
    }

    public:
    static InputManager* getInstance() {
        if (!_instance)
            _instance = new InputManager();
        return _instance;
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
};