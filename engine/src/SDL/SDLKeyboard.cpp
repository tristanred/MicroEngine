#include "SDL/SDLKeyboard.h"

#include <string.h>

SDLKeyboard::SDLKeyboard()
{
    keysCount = 512;
    currentScancodes = new Uint8[keysCount]{ 0 };
    previousScancodes = new Uint8[keysCount]{ 0 };
}


SDLKeyboard::~SDLKeyboard()
{
    delete(currentScancodes);
    delete(previousScancodes);
}

bool SDLKeyboard::IsKeyPressed(Key key)
{
    return currentScancodes[key];
}

bool SDLKeyboard::IsKeyClicked(Key key)
{
    return currentScancodes[key] && !previousScancodes[key];
}

bool SDLKeyboard::IsKeyDown(Key key)
{
    return currentScancodes[key];
}

bool SDLKeyboard::IsKeyUp(Key key)
{
    return currentScancodes[key] == false;
}

void SDLKeyboard::UpdateKeyboardState()
{
    memcpy(previousScancodes, currentScancodes, keysCount);

    currentScancodes = SDL_GetKeyboardState(&keysCount);
}

void SDLKeyboard::UpdateKeyboardPastState()
{
    // Nothing to do
}
