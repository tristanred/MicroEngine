#pragma once

#include <SDL_events.h>
#include <SDL_scancode.h>

#include <vector>
#include "libtech/pair.h"

#include "Input/AKeyboard.h"


class SDLKeyboard : public AKeyboard
{
public:
    SDLKeyboard();
    ~SDLKeyboard();

    bool IsKeyPressed(Key key) override;

    bool IsKeyClicked(Key key) override;

    void UpdateKeyboardState() override;
    void UpdateKeyboardPastState() override;

private:
    int keysCount;
    Uint8* previousScancodes;
    const Uint8* currentScancodes;
};

