#pragma once

#if SUPPORT_COCOA == 1

#include <vector>
#include "libtech/pair.h"
#include "Input/AKeyboard.h"

class CocoaKeyboard : public AKeyboard
{
public:
    CocoaKeyboard();
    virtual ~CocoaKeyboard();

    bool IsKeyPressed(Key key) override;
    bool IsKeyClicked(Key key) override;
    bool IsKeyDown(Key key) override;
    bool IsKeyUp(Key key) override;

    void UpdateKeyboardState() override;
    void UpdateKeyboardPastState() override;

private:
    int keysCount;
    uint8_t* previousScancodes;
    uint8_t* currentScancodes;
};
#endif
