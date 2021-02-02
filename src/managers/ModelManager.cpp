#include "ModelManager.h"


namespace Project {
ModelManager::ModelManager() {
    _zoom = glm::vec3(1, 1, 1);
}

void ModelManager::addModel(int id, Model model) {
    auto search = _models.find(id);
    if (search == _models.end()) {
        auto it = _models.begin();
        _models.insert(it, std::pair<int, std::vector<Model>>(id, std::vector<Model>()));
    }
    
    auto list = search->second;
    list.insert(list.end(), model);
}

std::vector<Model> ModelManager::getModels(int id) {
    return _models.at(id);
}

glm::vec3 ModelManager::getZoom() {
    return _zoom;
}
}