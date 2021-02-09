#include "DrawContext.h"

Project::DrawContext::DrawContext(GLFWwindow* window) {
    _window = window;
    _transformations = std::vector<Project::TransformationContext>();
    _modelId = 0;
}

/**
 * Returns the model id for user input.
 * 
 * @return model id to perform user input on.
 **/
int Project::DrawContext::getModelId() {
    return _modelId;
}

/**
 * Returns the window from which the drawing should be done on.
 **/
GLFWwindow* Project::DrawContext::getWindow() {
    return _window;
}

void Project::DrawContext::push(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale) {
    auto context = Project::TransformationContext(translation, rotation, scale);
    _transformations.push_back(context);
}

Project::TransformationContext Project::DrawContext::pop() {
    if (_transformations.size() > 0) {
        auto context = _transformations.back();
        _transformations.pop_back();
        return context;
    }
    return Project::TransformationContext(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
}

Project::TransformationContext Project::DrawContext::peek() {
    if (_transformations.size() > 0) {
        return _transformations.back();
    }
    return Project::TransformationContext(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
}