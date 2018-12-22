#pragma once

class GameEngine;

#include "core.h"
#include "CBaseControl.h"
#include <libtech/geometry.h>

class ENGINE_CLASS CLabel : public CBaseControl
{
public:
    CLabel(GameEngine* engine);
    ~CLabel();


};
