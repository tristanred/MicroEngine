#pragma once

#include "core.h"

class ARenderer;

/**
 * Abstract platform class. The platform is the middle layer in charge of 
 * responding to specific platform events.
 */
class ENGINE_CLASS APlatform
{
public:
    APlatform(ARenderer* renderer);
    virtual ~APlatform();
    
    // Platform State
    bool RequestExit;
    
    virtual void HandleEvents() = 0;

    virtual void Shutdown() = 0;
protected:
    ARenderer* Renderer;
};