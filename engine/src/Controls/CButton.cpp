#include "Controls/CButton.h"

#include <libtech/geometry.h>

#include "Input/AKeyboard.h"
#include "Input/AMouse.h"

CButton::CButton(GameEngine* engine) : CBaseControl(engine)
{
    this->CurrentState = Button_State::ENABLED;
    this->isEnabled = true;
    this->clickLock = false;

    this->enabledTexture = NULL;
    this->disabledTexture = NULL;
    this->downTexture = NULL;
    this->mouseOverTexture = NULL;
}

CButton::~CButton() {}

void CButton::Initialize(FSize size,
                         ATexture* enabledTexture,
                         ATexture* disabledTexture,
                         ATexture* downTexture,
                         ATexture* overTexture)
{
    CBaseControl::Initialize();

    this->SetSize(size);
    this->SetPosition(0, 0);

    this->enabledTexture = enabledTexture;
    this->disabledTexture = disabledTexture;
    this->downTexture = downTexture;
    this->mouseOverTexture = overTexture;
}

void CButton::Update(unsigned int deltaTime)
{
    CBaseControl::Update(deltaTime);

    if(this->IsEnabled())
    {
        // TODO : Viewport offset will screw up the mouse position, update to
        //        make sure that the viewport is taken into account.

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

                // When going back into Hovered mode, reset the clicked lock
                // flag
                this->clickLock = false;
            }
        }
        else
        {
            this->CurrentState = Button_State::ENABLED;

            // When going back into Enabled mode, reset the clicked lock flag
            this->clickLock = false;
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

bool CButton::IsClicked(bool clickedLockButton)
{
    // If the button is clicked
    if(this->IsEnabled() && this->CurrentState == Button_State::DOWN)
    {
        // Check that the button is not locked
        if(this->clickLock == false)
        {
            if(clickedLockButton == true)
            {
                this->clickLock = true;
            }

            return true;
        }
    }

    return false;
}
