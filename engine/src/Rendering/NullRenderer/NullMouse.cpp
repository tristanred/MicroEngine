#include "Rendering/NullRenderer/NullMouse.h"

NullMouse::NullMouse() {}

NullMouse::~NullMouse() {}

bool NullMouse::IsClicked()
{
    return false;
}

bool NullMouse::IsClicked(MouseButtons button)
{
    return false;
}

vec2 NullMouse::GetMousePosition()
{
    return vec2(0, 0);
}

void NullMouse::UpdateMouseState() {}
