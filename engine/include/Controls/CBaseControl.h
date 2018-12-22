#pragma once

class GameEngine;
class AMouse;
class AKeyboard;
class ARenderable;

#include "core.h"
#include <libtech/geometry.h>
#include "ARenderable.h"

/*
 * Base control class for all engine controls such as buttons, textboxes, etc.
 *
 * Controls are created by the Engine and exposed to GameModules using helper
 * methods such as module->CreateControl<CButton>();
 *
 * Control classes MUST call CBaseControl::Initialize() or the control will not
 * be active. This is to ensure that the base class has a hook and receives at
 * least a call to Initialize itself after the constructor.
 *
 * Remark: A control is not directly drawable so it does not inherit from
 * "ARenderable". This is because types inheriting from ARenderable are meant
 * to participate in the Abstract Rendering Layer.
*/
class ENGINE_CLASS CBaseControl : public ARenderable
{
public:
    CBaseControl(GameEngine* engine);
    ~CBaseControl();

    // Used to check is the control initializer was called
    bool IsInitialized();

    virtual void Update();

protected:
    // IO Objects
    AMouse* Mouse;
    AKeyboard* Keyboard;

    // Init call for the control, must be called from control classes
    void Initialize();

private:
    GameEngine* Engine;
    bool initializeCalled;
};
