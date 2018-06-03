#pragma once

#include "Keys.h"

class AKeyboard
{
public:
    virtual bool IsKeyPressed(Key key) = 0;

    virtual bool IsKeyClicked(Key key) = 0;

    virtual void UpdateKeyboardState() = 0;
    virtual void UpdateKeyboardPastState() = 0;

};