#include "Game/Physics/Physics.h"

PhysicsObject::PhysicsObject()
{
    this->Velocity = vec2(0, 0);
    this->Position = vec2(0, 0);

    this->CollisionPolygons = NULL;
}

PhysicsObject::~PhysicsObject()
{

}

bool PhysicsObject::IsCollision(PhysicsObject* other, CollisionCheckStrategy strategy)
{
    (void)strategy;

    // Check each of my polygons agains all other polygons of the other
    for(int i = 0; i < this->CollisionPolygons->Count(); i++)
    {
        FPolygon* myPolygon = this->CollisionPolygons->Get(i);

        for(int k = 0; k < other->CollisionPolygons->Count(); k++)
        {
            FPolygon* otherPolygon = other->CollisionPolygons->Get(k);

            if(myPolygon->IsCollision(otherPolygon))
            {
                return true;
            }
        }
    }

    return false;
}