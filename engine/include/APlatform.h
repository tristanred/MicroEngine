#pragma once

#include "core.h"

class ARenderer;

class ENGINE_CLASS APlatform
{
public:
    APlatform(ARenderer* renderer);
    ~APlatform();
    
    // Platform State
    bool RequestExit;
    
    virtual void HandleEvents() = 0;

    virtual void Shutdown() = 0;
protected:
    ARenderer* Renderer;
};