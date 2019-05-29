#pragma once

class ARenderer;

#include "core.h"
#include "APlatform.h"

class ENGINE_CLASS CocoaPlatform : public APlatform
{
public:
    CocoaPlatform(ARenderer* renderer);
    virtual ~CocoaPlatform();

    void HandleEvents() override;

    void Shutdown() override;
};