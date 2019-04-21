#pragma once

#include "core.h"

class ARenderer;

/**
 * \brief Abstract platform class.
 *
 * The platform is the middle layer in charge of responding to specific
 * platform events.
 */
class ENGINE_CLASS APlatform
{
public:
    APlatform(ARenderer* renderer);
    virtual ~APlatform();

    // Platform State
    bool RequestExit;

    /**
     * \brief Handle events raised by the current platorm.
     *
     * Usually used for pumping events out of the WIN32 message queue for
     * example or Linux signals.
     */
    virtual void HandleEvents() = 0;

    /**
     * \brief Clear resources associated with the this class.
     *
     * Usually called when the engine shuts itself down.
     */
    virtual void Shutdown() = 0;

protected:
    ARenderer* Renderer;
};