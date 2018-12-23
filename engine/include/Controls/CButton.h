#pragma once

class GameEngine;
class ATexture;
class AMouse;
class AKeyboard;

#include "core.h"
#include "CBaseControl.h"

class ENGINE_CLASS CButton : public CBaseControl
{
public:
    enum Button_State
    {
        ENABLED,
        DISABLED,
        DOWN,
        HOVERED
    };

    Button_State CurrentState;

    CButton(GameEngine* engine);
    ~CButton();

    void Initialize(FSize size, ATexture* enabledTexture = NULL, ATexture* disabledTexture = NULL, ATexture* downTexture = NULL, ATexture* overTexture = NULL);

    void Update() override;

    bool IsEnabled();
    void Enable(bool status);
    
    bool IsClicked(bool clickedLockButton = false);

    ATexture* GetTexture() override;

private:
    bool isEnabled;

    /*
     * The lock is used to avoid repeats of the IsClicked result. If we press
     * down a button and leave the mouse down and if the caller keeps calling
     * IsClicked every frame, the button will stay clicked and keep going into
     * the check if clicked. The IsClicked check might only want to trigger
     * once on every click. Every time we go back from the DOWN state, we reset
     * the lock to false. As long as the lock is true, the IsClicked will not
     * return true.
     */
    bool clickLock;
    
    ATexture* enabledTexture;
    ATexture* disabledTexture;
    ATexture* downTexture;
    ATexture* mouseOverTexture;
};
