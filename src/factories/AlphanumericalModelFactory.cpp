#include "AlphanumericalModelFactory.h"
//#include "../models/alphanumericals/ModelS.cpp"
//#include "../models/alphanumericals/ModelT.cpp"

namespace Project {
/**
 * This creates models based on input. This currently does not support
 * every letter and number.
 * 
 * Normally, this should be resolved through dependency injection,
 * but due to the size of the project this will be a singleton.
 **/
AlphanumbericalModelFactory::AlphanumbericalModelFactory() {

}

Model* AlphanumbericalModelFactory::createModelFor(char ch) {
    /*switch (ch) {
        case 'S':
            return new ModelS();
        case 'T':
            return new ModelT();
    }
    return new ModelS();*/
    return NULL;
}

Model* AlphanumbericalModelFactory::createModelFor(std::string chars) {
    // TODO: generalize the 2-letter 2-digit model?
    if (chars == "ts47") {
        // return model with TS47
    }
    return NULL;
}
}