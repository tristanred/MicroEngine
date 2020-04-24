#pragma once

class GameEngine;
class AMouse;
class AKeyboard;
class RenderableObject;

#include <libtech/geometry.h>

#include "Rendering/RenderableObject.h"
#include "core.h"

/**
 * Base control class for all engine controls such as buttons, textboxes, etc.
 *
 * Controls are created by the Engine and exposed to GameModules using helper
 * methods such as module->CreateControl<CButton>();
 *
 * Control classes MUST call CBaseControl::Initialize() or the control will not
 * be active. This is to ensure that the base class has a hook and receives at
 * least a call to Initialize itself after the constructor. Also, calling
 * Initialize allows callers to give parameters to the new object because they
 * can't call the constructor directly.
 *
 * Remark: A control is not directly drawable so it does not inherit from
 * "RenderableObject". This is because types inheriting from RenderableObject
 * are meant to participate in the Abstract Rendering Layer.
 */
class ENGINE_CLASS CBaseControl : public RenderableObject
{
public:
    CBaseControl(GameEngine* engine);
    ~CBaseControl();

    /**
     * Checks that the Initialization method was called. Should be checked
     * before doing operations on the control.
     *
     * Control classes deriving from CBaseControl should call the protected
     * method Initialize() when they are done with their setup stuff.
     */
    bool IsInitialized();

    /**
     * Update the control's logic.
     */
    virtual void Update(unsigned int deltaTime) override;

protected:
    GameEngine* GetEngine();

    // IO Objects
    AMouse* Mouse;
    AKeyboard* Keyboard;

    /**
     * Init call for the control, must be called from control classes. This is
     * needed because the CBaseControl may have to do special logic on the
     * GameEngine before the control is ready for gameplay.
     */
    void Initialize();

private:
    GameEngine* Engine;
    bool initializeCalled;
};
