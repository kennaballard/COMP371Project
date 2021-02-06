#include "AlphanumericalModelFactory.h"
//#include "../models/alphanumericals/ModelS.cpp"
#include "../models/alphanumericals/ModelT.cpp"

/**
 * This creates models based on input. This currently does not support
 * every letter and number.
 * 
 * Normally, this should be resolved through dependency injection,
 * but due to the size of the project this will be a singleton.
 **/
Project::AlphanumbericalModelFactory::AlphanumbericalModelFactory() {

}

Project::Model* Project::AlphanumbericalModelFactory::createModelFor(char ch, glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 rotation = glm::vec3(0, 0, 0), glm::vec3 scale = glm::vec3(1, 1, 1)) {
    switch (ch) {
        /*case 'S':
            return new ModelS();*/
        case 'T':
            return new ModelT(position, rotation, scale);
    }
    //return new ModelS();

    return NULL;
}

Project::Model* Project::AlphanumbericalModelFactory::createModelFor(std::string chars) {
    // TODO: generalize the 2-letter 2-digit model?
    if (chars == "ts47") {
        // return model with TS47
    }
    return NULL;
}