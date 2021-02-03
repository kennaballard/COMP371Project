#include "../models/Model.h"
#include <string>

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
    private:
    AlphanumbericalModelFactory();

    public:
    static AlphanumbericalModelFactory getInstance();
    Model* createModelFor(char ch);
    Model* createModelFor(std::string chars);
};