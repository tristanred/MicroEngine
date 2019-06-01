#ifdef SUPPORT_COCOA

#include "Cocoa/CocoaMouse.h"

CocoaMouse::CocoaMouse()
{

}

CocoaMouse::~CocoaMouse()
{

}

void CocoaMouse::UpdateMouseState()
{

}

bool CocoaMouse::IsClicked()
{
    return false;
}

bool CocoaMouse::IsClicked(MouseButtons button)
{
    return false;
}

vec2 CocoaMouse::GetMousePosition()
{
    return vec2(0, 0);
}
#endif
