#pragma once

#include "core.h"
#include "libtech/vec.h"

enum MouseButtons
{
    LEFT,
    RIGHT,
    MIDDLE,
    BUTTON3,
    BUTTON4,
};

enum ButtonState
{
    BTN_CLICKED,
    BTN_RELEASED
};

class ENGINE_CLASS AMouse {
public:
    AMouse();
    virtual ~AMouse();

    virtual bool IsClicked() = 0;
    virtual bool IsClicked(MouseButtons button) = 0;

    virtual void UpdateMouseState() = 0;
    void UpdatePastMouseState();

    ButtonState Left_Previous_State;
    ButtonState Right_Previous_State;
    ButtonState Middle_Previous_State;

    ButtonState Left_Current_State;
    ButtonState Right_Current_State;
    ButtonState Middle_Current_State;

    bool LeftButtonUp();
    bool RightButtonUp();
    bool MiddleButtonUp();

    bool LeftButtonDown();
    bool RightButtonDown();
    bool MiddleButtonDown();


    // Clicked is when a button was down and just got unclicked. Triggered once by up/down cycle
    bool LeftButtonClicked();
    bool RightButtonClicked();
    bool MiddleButtonClicked();

    // Pressed is when a button was up and just got clicked. Triggered once by up/down cycle
    bool LeftButtonPressed();
    bool RightButtonPressed();
    bool MiddleButtonPressed();

    virtual vec2 GetMousePosition() = 0;
};