#include "ModelManager.h"


Project::ModelManager::ModelManager() {
    _zoom = glm::vec3(1, 1, 1);
}

void Project::ModelManager::addModel(int id, Project::Model *model) {
    if (_models.find(id) == _models.end()) {
        _models.insert(std::make_pair(id, std::vector<Project::Model*>()));
    }
    _models.at(id).push_back(model);
}

std::vector<Project::Model*> Project::ModelManager::getModels(int id) {
    return _models.at(id);
}

glm::vec3 Project::ModelManager::getZoom() {
    return _zoom;
}