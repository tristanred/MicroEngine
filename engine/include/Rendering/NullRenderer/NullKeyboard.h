#pragma once

#include <vector>

#include "Input/AKeyboard.h"
#include "core.h"

class ENGINE_CLASS NullKeyboard : public AKeyboard
{
public:
    NullKeyboard();
    ~NullKeyboard();

    bool IsKeyPressed(Key key) override;
    bool IsKeyClicked(Key key) override;
    bool IsKeyDown(Key key) override;
    bool IsKeyUp(Key key) override;

    void UpdateKeyboardState() override;
    void UpdateKeyboardPastState() override;
};