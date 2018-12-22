#pragma once

#include "core.h"
#include "ARenderable.h"
#include "CBaseControl.h"
#include <libtech/Geometry.h>

class ATexture;
class AMouse;
class AKeyboard;

/*
Button states :

Idle
Disabled
Pressed
MouseOver

*/

class ENGINE_CLASS CButton : public CBaseControl
{
public:
    CButton(FSize size, ATexture* idleTex = NULL, ATexture* disabledTex = NULL, ATexture* pressedTex = NULL, ATexture* overTex = NULL);
    ~CButton();

    void DoStuff() override;

};