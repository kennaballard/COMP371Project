#include "ModelManager.h"
#include "../models/Model.cpp"
#include <map>

class ModelManager {
    private:
    static ModelManager* _instance;
    std::map<int, std::vector<Model>> _models;
    glm::vec3 _zoom;

    ModelManager() {
        _zoom = glm::vec3(1, 1, 1);
    }

    public:
    static ModelManager* getInstance() {
        if (!_instance)
            _instance = new ModelManager();
        return _instance;
    }

    std::vector<Model> ModelManager::getModels(int id) {
        return _models.at(id);
    }

    glm::vec3 ModelManager::getZoom() {
        return _zoom;
    }
};