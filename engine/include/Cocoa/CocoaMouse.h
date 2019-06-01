#pragma once

#ifdef SUPPORT_COCOA

#include "libtech/vec.h"
#include "Input/AMouse.h"

class CocoaMouse : public AMouse
{
public:
    CocoaMouse();
    virtual ~CocoaMouse();

    void UpdateMouseState() override;

    bool IsClicked() override;
    bool IsClicked(MouseButtons button) override;

    vec2 GetMousePosition() override;

private:
    float MouseCoordX = 0;
    float MouseCoordY = 0;
};

#endif