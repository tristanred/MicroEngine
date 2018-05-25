#pragma once

#include "core.h"

class ENGINE_CLASS ASprite
{
    ASprite();
    ~ASprite();
    
    virtual void Draw() = 0;
};