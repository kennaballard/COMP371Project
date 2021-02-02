#include "AlphanumericalModelFactory.h"
#include "../models/alphanumericals/ModelS.cpp"
#include "../models/alphanumericals/ModelT.cpp"

/**
 * This creates models based on input. This currently does not support
 * every letter and number.
 * 
 * Normally, this should be resolved through dependency injection,
 * but due to the size of the project this will be a singleton.
 **/
class AlphanumbericalModelFactory {
    private:
    static AlphanumbericalModelFactory *_instance;

    AlphanumbericalModelFactory() {

    }

    public:
    static AlphanumbericalModelFactory* getInstance() {
        if (!_instance)
            _instance = new AlphanumbericalModelFactory();
        return _instance;
    }

    Model* createModelFor(char ch) {
        switch (ch) {
            case 'S':
                return new ModelS();
            case 'T':
                return new ModelT();
        }
    }

    Model* createModelFor(std::string chars) {
        // TODO: generalize the 2-letter 2-digit model?
        if (chars == "ts47") {
            // return model with TS47
        }
    }
};