#pragma once

#include "core.h"
#include <libtech/Geometry.h>

/*
 * Base control class for all engine controls such as buttons, textboxes, etc.
 *
 * Remark: A control is not directly drawable so it does not inherit from
 * "ARenderable". This is because types inheriting from ARenderable are meant
 * to participate in the Abstract Rendering Layer.
*/
class ENGINE_CLASS CBaseControl
{
public:
    CBaseControl(FSize size);
    ~CBaseControl();

    FSize ControlSize;
    FPosition ControlPosition;

    virtual void Update();

    virtual void DoStuff() = 0;
private:
};