#include "../models/Model.h"

/**
 * Stores & manages models to use throughout the codebase.
 * This will also return a list of models, sorted in ascending
 * order of depth (z-index) if needed (not implemented yet),
 * to draw.
 * 
 * Normally, this should be resolved through dependency injection,
 * but due to the size of the project this will be a singleton.
 **/
class ModelManager {
    public:
    /**
     * Adds a model to store to the manager.
     * 
     * @param id the scene id
     * @param model the new model
     **/
    void addModel(int id, Model model);
    /**
     * Returns a list of models to draw
     * in order of added.
     * 
     * @param id the scene id
     **/
    std::vector<Model> getModels(int id);
    /**
     * Return the zoom level in a vector 3, corresponding to each
     * zoom level for that axis.
     **/
    glm::vec3 getZoom();
};