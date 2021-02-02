#ifndef InputHandlerH
#define InputHandlerH

namespace Project {
class InputHandler {
    public:
    /**
     * Handles input events.
     * 
     * TODO: might need data objects to pass data in.
     * TODO: might need more classes to separate mouse vs keyboard events.
     * TODO: might need special events for mouse drag and other specific events.
     **/
    virtual void handle();
};
}
#endif