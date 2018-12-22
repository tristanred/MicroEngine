#pragma once

#include "core.h"
#include "CBaseControl.h"
#include <libtech/Geometry.h>

class ENGINE_CLASS CLabel : public CBaseControl
{
public:
    CLabel(FSize size);
    ~CLabel();

    void DoStuff() override;

};