#include "Rendering/NullRenderer/NullKeyboard.h"

#include <string.h>

NullKeyboard::NullKeyboard() {}

NullKeyboard::~NullKeyboard() {}

bool NullKeyboard::IsKeyPressed(Key key)
{
    return false;
}

bool NullKeyboard::IsKeyClicked(Key key)
{
    return false;
}

bool NullKeyboard::IsKeyDown(Key key)
{
    return false;
}

bool NullKeyboard::IsKeyUp(Key key)
{
    return false;
}

void NullKeyboard::UpdateKeyboardState() {}

void NullKeyboard::UpdateKeyboardPastState() {}