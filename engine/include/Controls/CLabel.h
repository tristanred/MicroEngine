#pragma once

class GameEngine;

#include <libtech/geometry.h>

#include "CBaseControl.h"
#include "core.h"

class ENGINE_CLASS CLabel : public CBaseControl
{
public:
    CLabel(GameEngine* engine);
    ~CLabel();
};
