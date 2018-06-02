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

    virtual bool IsKeyPressed(Key key);

    virtual bool IsKeyClicked(Key key);

    virtual void UpdateKeyboardState();

private:
    int keysCount;
    Uint8* previousScancodes;
    const Uint8* currentScancodes;
};

