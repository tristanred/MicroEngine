#pragma once

#include "Keys.h"

class AKeyboard
{
public:
    AKeyboard() = default;
    virtual ~AKeyboard() = default;

    virtual bool IsKeyPressed(Key key) = 0;
    virtual bool IsKeyClicked(Key key) = 0;
    virtual bool IsKeyDown(Key key) = 0;
    virtual bool IsKeyUp(Key key) = 0;

    virtual void UpdateKeyboardState() = 0;
    virtual void UpdateKeyboardPastState() = 0;
};