#pragma once

#include <SDL_events.h>

#include "libtech/vec.h"

#include "Input/AMouse.h"

class SDLMouse : public AMouse
{
public:
    SDLMouse();
    ~SDLMouse();

    virtual bool IsClicked();
    virtual bool IsClicked(MouseButtons button);

    virtual vec2 GetMousePosition();

    void HandleEvent(SDL_Event* anEvent);

private:
    float MouseCoordX = 0;
    float MouseCoordY = 0;

    //bool leftButtonClicked = false;
    //bool rightButtonClicked = false;
    //bool middleButtonClicked = false;
    //bool fourthButtonClicked = false;
    //bool fifthButtonClicked = false;

};

