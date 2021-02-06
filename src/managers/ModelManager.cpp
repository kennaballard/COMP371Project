#include "ModelManager.h"


Project::ModelManager::ModelManager() {
    _zoom = glm::vec3(1, 1, 1);
}

void Project::ModelManager::addModel(int id, Project::Model* model) {
    auto search = _models.find(id);
    if (search == _models.end()) {
        search = _models.insert(std::make_pair(id, std::vector<Project::Model*>())).first;
    }
    
    auto list = search->second;
    list.insert(list.begin(), model);
}

std::vector<Project::Model*> Project::ModelManager::getModels(int id) {
    return _models.at(id);
}

glm::vec3 Project::ModelManager::getZoom() {
    return _zoom;
}