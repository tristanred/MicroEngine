#pragma once

#include "core.h"
#include "ARenderable.h"

class ENGINE_CLASS ASprite : public ARenderable
{
public:
    ASprite(ARenderer* renderer);
    virtual ~ASprite() override;
};


