#pragma once

#include "core.h"

template <class TInner = void>
class ENGINE_CLASS ITraversable
{
public:
    TInner* inner = NULL;

    virtual bool IsPassable() = 0;

    virtual ITraversable* Left() = 0;
    virtual ITraversable* Up() = 0;
    virtual ITraversable* Right() = 0;
    virtual ITraversable* Down() = 0;

    virtual ITraversable* Up_Left() = 0;
    virtual ITraversable* Up_Right() = 0;
    virtual ITraversable* Down_Right() = 0;
    virtual ITraversable* Down_Left() = 0;
};
