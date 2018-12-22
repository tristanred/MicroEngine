#include "Controls/CButton.h"

#include "Input/AMouse.h"
#include "Input/AKeyboard.h"
#include <libtech/geometry.h>

CButton::CButton(GameEngine* engine) : CBaseControl(engine)
{
    this->CurrentState = Button_State::ENABLED;
    this->isEnabled = true;
}

CButton::~CButton()
{

}

void CButton::Initialize(FSize size, ATexture* enabledTexture, ATexture* disabledTexture, ATexture* downTexture, ATexture* overTexture)
{
    CBaseControl::Initialize();

    this->SetSize(size);
    this->SetPosition(0, 0);

    this->enabledTexture = enabledTexture;
    this->disabledTexture = disabledTexture;
    this->downTexture = downTexture;
    this->mouseOverTexture = overTexture;
}

void CButton::Update()
{
    CBaseControl::Update();

    if(this->IsEnabled())
    {
        // Check if mouse is over the rectangle
        FRectangle rec = this->GetRectangle();
        if(rec.PointIsInside(this->Mouse->GetMousePosition()))
        {
            bool mouseClicked = this->Mouse->LeftButtonDown();
            if(mouseClicked)
            {
                this->CurrentState = Button_State::DOWN;
            }
            else
            {
                this->CurrentState = Button_State::HOVERED;
            }
        }
        else
        {
            this->CurrentState = Button_State::ENABLED;
        }
    }
}

ATexture* CButton::GetTexture()
{
    ATexture* tex;

    // Return a different texture depending on the state. If the button is in a
    // state and there is no texture assigned use the enabled one.
    switch(CurrentState)
    {
        case Button_State::ENABLED:
        {
            tex = this->enabledTexture;

            break;
        }
        case Button_State::DISABLED:
        {
            if(this->disabledTexture != NULL)
            {
                tex = this->disabledTexture;
            }
            else
            {
                tex = this->enabledTexture;
            }

            break;
        }
        case Button_State::DOWN:
        {
            if(this->downTexture != NULL)
            {
                tex = this->downTexture;
            }
            else
            {
                tex = this->enabledTexture;
            }

            break;
        }
        case Button_State::HOVERED:
        {
            if(this->mouseOverTexture != NULL)
            {
                tex = this->mouseOverTexture;
            }
            else
            {
                tex = this->enabledTexture;
            }

            break;
        }
    }

    return tex;
}

bool CButton::IsEnabled()
{
    return isEnabled;
}

void CButton::Enable(bool status)
{
    if(status)
    {
        this->CurrentState = Button_State::ENABLED;
    }
    else
    {
        this->CurrentState = Button_State::DISABLED;
    }

    this->isEnabled = status;
}
