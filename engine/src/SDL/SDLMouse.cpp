#include "SDL/SDLMouse.h"


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

            if (this->Left_Current_State == BTN_CLICKED)
            {
                return true;
            }
            else
            {
                return false;
            }

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

void SDLMouse::HandleEvent(SDL_Event* anEvent)
{
    // Needed ?
    //leftButtonClicked = false;
    //rightButtonClicked = false;
    //middleButtonClicked = false;
    //fourthButtonClicked = false;
    //fifthButtonClicked = false;

    switch (anEvent->type)
    {
        case SDL_MOUSEMOTION:
        {
            this->MouseCoordX = (float)anEvent->motion.x;
            this->MouseCoordY = (float)anEvent->motion.y;

            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            switch (anEvent->button.button)
            {
                case SDL_BUTTON_LEFT:
                {
                    this->Left_Current_State = BTN_CLICKED;

                    break;
                }
                case SDL_BUTTON_MIDDLE:
                {
                    this->Middle_Current_State = BTN_CLICKED;

                    break;
                }
                case SDL_BUTTON_RIGHT:
                {
                    this->Right_Current_State = BTN_CLICKED;

                    break;
                }
                    //case SDL_BUTTON_X1:
                    //{
                    //    this->fourthButtonClicked = true;

                    //    break;
                    //}
                    //case SDL_BUTTON_X2:
                    //{
                    //    this->fifthButtonClicked = true;

                    //    break;
                    //}

                default:
                    break;
            }

            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            switch (anEvent->button.button)
            {
                case SDL_BUTTON_LEFT:
                {
                    this->Left_Current_State = BTN_RELEASED;

                    break;
                }
                case SDL_BUTTON_MIDDLE:
                {
                    this->Middle_Current_State = BTN_RELEASED;

                    break;
                }
                case SDL_BUTTON_RIGHT:
                {
                    this->Right_Current_State = BTN_RELEASED;

                    break;
                }

                default:
                    break;
            }

            break;
        }

        default:
            break;
    }
}
