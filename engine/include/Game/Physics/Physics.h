#pragma once

#include "core.h"

#include <libtech/geometry.h>
#include <libtech/vec.h>
#include <libtech/arraylist.h>

class PhysicsObject;

class ENGINE_CLASS IPhysicsContainer
{
public:
    virtual PhysicsObject* GetPhysicsObject() = 0;
};

enum CollisionCheckStrategy
{
    COARSE, // Only do coarse checks
    PRECISE, // Only do precise checks
    FULL // Execute a coarse check first and a precise check if needed.
};

class ENGINE_CLASS PhysicsObject
{
public:
    PhysicsObject();
    ~PhysicsObject();

    vec2 Velocity;
    vec2 Position;

    ArrayList<FPolygon*>* CollisionPolygons;

    bool IsCollision(PhysicsObject* other, CollisionCheckStrategy strategy = FULL);
};