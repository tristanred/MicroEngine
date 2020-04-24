#pragma once

#ifdef SUPPORT_SDL

#include <SDL_events.h>

#include "Input/AMouse.h"
#include "libtech/vec.h"

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

#endif