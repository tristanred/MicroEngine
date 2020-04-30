#pragma once

#include "Input/AMouse.h"
#include "libtech/vec.h"
#include "core.h"

class ENGINE_CLASS NullMouse : public AMouse
{
public:
    NullMouse();
    ~NullMouse();

    void UpdateMouseState() override;

    bool IsClicked() override;
    bool IsClicked(MouseButtons button) override;

    vec2 GetMousePosition() override;
};