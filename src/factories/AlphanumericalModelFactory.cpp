#include "AlphanumericalModelFactory.h"
//#include "../models/alphanumericals/ModelS.cpp"
//#include "../models/alphanumericals/ModelT.cpp"

//ModelKennedy
#include "../models/alphanumericals/ModelK.cpp"
#include "../models/alphanumericals/ModelY.cpp"
#include "../models/alphanumericals/ModelA.cpp"
#include "../models/alphanumericals/ModelE.cpp"
#include "../models/alphanumericals/Model2.cpp"
#include "../models/alphanumericals/Model0.cpp"
#include "../models/alphanumericals/ModelAntoine.cpp"
#include "../models/alphanumericals/ModelKennedy.cpp"
#include "../models/alphanumericals/ModelL.cpp"
#include "../models/alphanumericals/Model8.cpp"
#include "../models/alphanumericals/ModelAna.cpp"
#include "../models/alphanumericals/ModelThomas.cpp"
#include "../models/Floor.cpp"
/**
 * This creates models based on input. This currently does not support
 * every letter and number.
 * 
 * Normally, this should be resolved through dependency injection,
 * but due to the size of the project this will be a singleton.
 **/
Project::AlphanumbericalModelFactory::AlphanumbericalModelFactory() {

}

Project::Model* Project::AlphanumbericalModelFactory::createModelFor(char ch, glm::vec3 position = glm::vec3(0, 0, 0), float rotation = 0.0f, glm::vec3 scale = glm::vec3(1, 1, 1)) {
    switch (ch) {
        /*case 'S':
            return new ModelS();*/
        /*case 'T':
            return new ModelT(position, rotation, scale);*/

        //ModelKennedy
        case '0': 
            return new Model0(glm::mat4(1.0f), position, rotation, scale);
        case '4K':
            return new Model4(glm::mat4(1.0f), position, rotation, scale);
        case 'K':
            return new ModelK(glm::mat4(1.0f), position, rotation, scale);
        case 'T':
            return new ModelT(glm::mat4(1.0f), position, rotation, scale);
        case 'Y':
            return new ModelY(glm::mat4(1.0f), position, rotation, scale);
       
        
        //ModelAna
        case 'A':
            return new ModelA(glm::mat4(1.0f), position, rotation, scale);
        case 'L':
            return new ModelL(glm::mat4(1.0f), position, rotation, scale);
        case '4':
            return new Model4(glm::mat4(1.0f), position, rotation, scale);
        case '8':
            return new Model8(glm::mat4(1.0f), position, rotation, scale);
        case '2':
            return new Model2(glm::mat4(1.0f), position, rotation, scale);

    }
    //return new ModelS();

    return NULL;
}

Project::Model* Project::AlphanumbericalModelFactory::createModelFor(std::string chars, glm::vec3 position = glm::vec3(0, 0, 0), float rotation = 0.0f, glm::vec3 scale = glm::vec3(1, 1, 1)) {
    // TODO: generalize the 2-letter 2-digit model?
    if (chars == "ts47") {
        return new ModelThomas(glm::mat4(1.0f), position, rotation, scale);
    } else if (chars == "ky40") {
        return new ModelKennedy(glm::mat4(1.0f),  position, rotation, scale);
    }
    if (chars == "ae20") {
        return new ModelAntoine(glm::mat4(1.0f), position, rotation, scale);
    }
    if (chars == "floor") {
        return new Floor(glm::mat4(1.0f), position, rotation, scale);
    }
    if (chars == "al48") {
        return new ModelAna(glm::mat4(1.0f), position, rotation, scale);
    }
    return NULL;
}