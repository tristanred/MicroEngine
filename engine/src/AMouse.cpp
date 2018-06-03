#include "Input/AMouse.h"


bool AMouse::LeftButtonUp()
{
    if (this->Left_Current_State == BTN_RELEASED)
    {
        return true;
    }

    return false;
}


bool AMouse::RightButtonUp()
{
    if (this->Right_Current_State == BTN_RELEASED)
    {
        return true;
    }

    return false;
}


bool AMouse::MiddleButtonUp()
{
    if (this->Middle_Current_State == BTN_RELEASED)
    {
        return true;
    }

    return false;
}


bool AMouse::LeftButtonDown()
{
    if (this->Left_Current_State == BTN_CLICKED)
    {
        return true;
    }

    return false;
}


bool AMouse::RightButtonDown()
{
    if (this->Right_Current_State == BTN_CLICKED)
    {
        return true;
    }

    return false;
}


bool AMouse::MiddleButtonDown()
{
    if (this->Middle_Current_State == BTN_CLICKED)
    {
        return true;
    }

    return false;
}

bool AMouse::LeftButtonClicked()
{
    if (Left_Current_State == BTN_RELEASED && Left_Previous_State == BTN_CLICKED)
    {
        return true;
    }

    return false;
}

bool AMouse::RightButtonClicked()
{
    if (Right_Current_State == BTN_RELEASED && Right_Previous_State == BTN_CLICKED)
    {
        return true;
    }

    return false;
}

bool AMouse::MiddleButtonClicked()
{
    if (Middle_Current_State == BTN_RELEASED && Middle_Previous_State == BTN_CLICKED)
    {
        return true;
    }

    return false;
}


bool AMouse::LeftButtonPressed()
{
    if (Left_Current_State == BTN_CLICKED && Left_Previous_State == BTN_RELEASED)
    {
        return true;
    }

    return false;
}


bool AMouse::RightButtonPressed()
{
    if (Right_Current_State == BTN_CLICKED && Right_Previous_State == BTN_RELEASED)
    {
        return true;
    }

    return false;
}


bool AMouse::MiddleButtonPressed()
{
    if (Middle_Current_State == BTN_CLICKED && Middle_Previous_State == BTN_RELEASED)
    {
        return true;
    }

    return false;
}

void AMouse::UpdatePastMouseState()
{
    Left_Previous_State = Left_Current_State;
    Right_Previous_State = Right_Current_State;
    Middle_Previous_State = Middle_Current_State;
}
