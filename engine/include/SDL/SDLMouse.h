#pragma once

#include <SDL_events.h>

#include "libtech/vec.h"

#include "Input/AMouse.h"

class SDLMouse : public AMouse
{
public:
    SDLMouse();
    ~SDLMouse();

    void UpdateMouseState() override;

    bool IsClicked() override;
    bool IsClicked(MouseButtons button) override;

    vec2 GetMousePosition() override;

private:
    float MouseCoordX = 0;
    float MouseCoordY = 0;
};

