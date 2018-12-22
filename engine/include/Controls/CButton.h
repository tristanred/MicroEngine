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

    ATexture* GetTexture() override;

private:
    bool isEnabled;

    ATexture* enabledTexture;
    ATexture* disabledTexture;
    ATexture* downTexture;
    ATexture* mouseOverTexture;
};
