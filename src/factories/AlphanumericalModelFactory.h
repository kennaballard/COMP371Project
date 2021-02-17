#pragma once
#include "../models/Model.h"
#include <string>

namespace Project {
    /**
     * This creates models based on input.
     * 
     * Normally, this should be resolved through dependency injection,
     * but due to the size of the project this will be a singleton.
     * 
     * TODO: is this needed? keep only if generalizing models is possible?
     * TODO: generalized grouped models? Draw children if some field is true.
     **/
    class AlphanumbericalModelFactory {
        public:
        AlphanumbericalModelFactory();
        Model* createModelFor(char ch, glm::vec3 position, float rotation, glm::vec3 scale);
        Model* createModelFor(std::string chars, glm::vec3 position, float rotation, glm::vec3 scale);
    };
}