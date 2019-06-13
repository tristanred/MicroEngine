#include "Controls/CBaseControl.h"

#include "GameEngine.h"
#include "Input/AMouse.h"
#include "Input/AKeyboard.h"

CBaseControl::CBaseControl(GameEngine* engine) : RenderableObject(engine)
{
    this->Engine = engine;
    this->Mouse = this->Engine->Mouse;
    this->Keyboard = this->Engine->Keyboard;

    this->SetSize(0, 0);
    this->SetPosition(0, 0);

    this->initializeCalled = false;
}

CBaseControl::~CBaseControl()
{

}

bool CBaseControl::IsInitialized()
{
    return this->initializeCalled;
}

void CBaseControl::Update()
{
    if(this->IsInitialized())
    {

    }
}

void CBaseControl::Initialize()
{
    this->initializeCalled = true;
}

GameEngine* CBaseControl::GetEngine()
{
    return this->Engine;
}
