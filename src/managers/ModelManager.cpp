#include "ModelManager.h"
#include <iostream>

Project::ModelManager::ModelManager() {
    _zoom = glm::vec3(1, 1, 1);
}

void Project::ModelManager::addModel(int id, Project::Model* model) {
    auto search = _models.find(id);
    if (search == _models.cend()) {
        search = _models.insert(std::pair<int, std::vector<Project::Model*>>(id, std::vector<Project::Model*>())).first;
    }
    
    auto list = search->second;
    list.insert(list.begin(), model);
}

std::vector<Project::Model*> Project::ModelManager::getModels(int id) {
   /* std::cout << id << std::endl;*/
    std::vector<Project::Model*> res = _models.at(id);
   /* std::cout << res.size() << std::endl;*/
    return _models.at(id);
}

glm::vec3 Project::ModelManager::getZoom() {
    return _zoom;
}