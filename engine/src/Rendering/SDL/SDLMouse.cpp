#ifdef SUPPORT_SDL

#include "Rendering/SDL/SDLMouse.h"

SDLMouse::SDLMouse()
{
    this->Left_Current_State = BTN_RELEASED;
    this->Right_Current_State = BTN_RELEASED;
    this->Middle_Current_State = BTN_RELEASED;

    this->Left_Previous_State = BTN_RELEASED;
    this->Right_Previous_State = BTN_RELEASED;
    this->Middle_Previous_State = BTN_RELEASED;
}


SDLMouse::~SDLMouse()
{
}

bool SDLMouse::IsClicked()
{
    return this->LeftButtonClicked() ||
           this->RightButtonClicked() ||
           this->MiddleButtonClicked();
}

bool SDLMouse::IsClicked(MouseButtons button)
{
    switch (button)
    {
        case LEFT:
            return this->Left_Current_State == BTN_CLICKED;
            break;
        case RIGHT:
            return this->Right_Current_State == BTN_CLICKED;
            break;
        case MIDDLE:
            return this->Middle_Current_State == BTN_CLICKED;
            break;
        default:
            return false;
            break;
    }
}

vec2 SDLMouse::GetMousePosition()
{
    vec2 pos;
    pos.x = MouseCoordX;
    pos.y = MouseCoordY;

    return pos;
}

void SDLMouse::UpdateMouseState()
{
    int x, y;
    Uint32 state = SDL_GetMouseState(&x, &y);

    this->MouseCoordX = (float)x;
    this->MouseCoordY = (float)y;

    bool leftButtonClicked = state & SDL_BUTTON(SDL_BUTTON_LEFT);
    this->Left_Current_State = leftButtonClicked ? BTN_CLICKED : BTN_RELEASED;

    bool rightButtonClicked = state & SDL_BUTTON(SDL_BUTTON_RIGHT);
    this->Right_Current_State = rightButtonClicked ? BTN_CLICKED : BTN_RELEASED;

    bool middleButtonClicked = state & SDL_BUTTON(SDL_BUTTON_MIDDLE);
    this->Middle_Current_State = middleButtonClicked ? BTN_CLICKED : BTN_RELEASED;
}
#endif