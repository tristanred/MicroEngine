#include "Controls/CBaseControl.h"

CBaseControl::CBaseControl(FSize size)
{
    this->ControlSize = size;
    this->ControlPosition = FPosition(0, 0);
}

CBaseControl::~CBaseControl()
{

}

void CBaseControl::Update()
{
    
}
