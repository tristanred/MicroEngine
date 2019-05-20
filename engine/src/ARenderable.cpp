#include "ARenderable.h"

#include "ATexture.h"

ARenderable::ARenderable(ARenderer* renderer)
{
    LogTrace("ARenderable::ARenderable");

    this->Renderer = renderer;

    this->Parent = NULL;
    this->Children = new ArrayList<ARenderable*>();

    this->texture = NULL;

    this->size = FSize(0, 0);
    this->position = FPosition(0, 0);
    this->scale = vec2(1, 1);
    this->PositionSystem = VIEWPORT_RELATIVE;
    this->isVisible = true;
}

ARenderable::~ARenderable()
{
    LogTrace("ARenderable::~ARenderable");

    this->Parent = NULL;
    delete(this->Children);
}

FRectangle ARenderable::GetRectangle()
{
    if(this->Children->Count() > 0)
    {
        FRectangle myChildBounds = FRectangle(0, 0, 0, 0);
        
        // Get max size of the children bounds
        for(int i = 0; i < this->Children->Count(); i++)
        {
            FRectangle target = this->Children->Get(i)->GetRectangle();
            
            if(target.Left() > myChildBounds.Left())
            {
                myChildBounds.X = target.Left();
            }
            if(target.Top() > myChildBounds.Top())
            {
                myChildBounds.Y = target.Top();
            }
            if(myChildBounds.Right() < target.Right())
            {
                myChildBounds.Width = target.Width;
            }
            if(myChildBounds.Bottom() < target.Bottom())
            {
                myChildBounds.Height = target.Height;
            }
        }
        
        FRectangle myRect = FRectangle(this->position, this->size);
        if(myChildBounds.Left() < myRect.Left())
        {
            myRect.X = myChildBounds.Left();
        }
        if(myChildBounds.Top() < myRect.Top())
        {
            myRect.Y = myChildBounds.Top();
        }
        if(myChildBounds.Right() > myRect.Right())
        {
            myRect.Width = myChildBounds.X + myChildBounds.Width;
        }
        if(myChildBounds.Bottom() > myRect.Bottom())
        {
            myRect.Height = myChildBounds.Y + myChildBounds.Height;
        }
        
        return myRect;
    }

    return FRectangle(this->position, this->size);
}

FPosition ARenderable::GetPosition()
{
    if(this->Parent == NULL)
    {
        return this->position;
    }
    else
    {
        FPosition calculatedResult = this->position;

        // TODO : Why not just call this->Parent->GetPosition() ?
        ARenderable* next = this->Parent;
        while(next != NULL)
        {
            FPosition nextPos = next->position;
            calculatedResult.X += nextPos.X;
            calculatedResult.Y += nextPos.Y;

            next = next->Parent;
        }

        return calculatedResult;
    }
}

void ARenderable::SetPosition(FPosition position)
{
    this->position = position;
}

void ARenderable::SetPosition(float x, float y)
{
    this->position.X = x;
    this->position.Y = y;
}

void ARenderable::SetPositionAnchored(FPosition position, vec2 anchor)
{
    auto currentSize = this->GetSize();
    
    auto sizeOffset = vec2(currentSize.Width * anchor.x, currentSize.Height * anchor.y);
    
    FPosition newPos = FPosition(this->position.X - sizeOffset.x, this->position.Y - sizeOffset.y);
    
    this->SetPosition(newPos);
}

FSize ARenderable::GetSize()
{
    FSize biggestSize = FSize(0, 0);
    for(int i = 0; i < this->Children->Count(); i++)
    {
        if(this->Children->Get(i)->GetSize().Width > biggestSize.Width)
        {
            biggestSize.Width = this->Children->Get(i)->GetSize().Width;
        }
        if(this->Children->Get(i)->GetSize().Height > biggestSize.Height)
        {
            biggestSize.Height = this->Children->Get(i)->GetSize().Height;
        }
    }

    if(this->size.Width > biggestSize.Width)
    {
        biggestSize.Width = this->size.Width;
    }
    if(this->size.Height > biggestSize.Height)
    {
        biggestSize.Height = this->size.Height;
    }

    vec2 totalScale = this->GetScale();
    biggestSize.Width *= totalScale.x;
    biggestSize.Height *= totalScale.y;

    return biggestSize;
}

void ARenderable::SetSize(FSize size)
{
    this->size = size;
}

void ARenderable::SetSize(float w, float h)
{
    this->size.Width = w;
    this->size.Height = h;

    ATexture* textureToResize = this->GetTexture();
    if(textureToResize != NULL)
    {
        textureToResize->SetSize(this->size);
    }
}

vec2 ARenderable::GetScale()
{
    vec2 finalScale = this->scale;
    
    // TODO : Work in progress. Won't work because the children are not added
    // to a scalable surface.
//    ARenderable* next = this->Parent;
//    while(next != NULL)
//    {
//        vec2 parentScale = next->GetScale();
//        finalScale.x *= parentScale.x;
//        finalScale.y *= parentScale.y;
//
//        next = next->Parent;
//    }
    
    return finalScale;
}

void ARenderable::SetScale(float scale)
{
    this->SetScale(scale, scale);
}

void ARenderable::SetScale(float x, float y)
{
    this->SetScale(vec2(x, y));
}

void ARenderable::SetScale(vec2 scale)
{
    this->scale = scale;
}

ATexture* ARenderable::GetTexture()
{
    return this->texture;
}

void ARenderable::SetTexture(ATexture* newTexture)
{
    if (this->texture != NULL)
        delete(this->texture);

    this->texture = newTexture;
}

enum POSITION_SYSTEM ARenderable::GetPositionSystem()
{
    return this->PositionSystem;
}

void ARenderable::SetPositionSystem(enum POSITION_SYSTEM value)
{
    this->PositionSystem = value;
}

bool ARenderable::IsVisible()
{
    if(this->isVisible == false)
    {
        return false;
    }

    if(this->Parent == NULL)
    {
        return isVisible;
    }
    else
    {
        ARenderable* next = this->Parent;
        while(next != NULL)
        {
            if(next->isVisible == false)
            {
                return false;
            }

            next = next->Parent;
        }

        return true;
    }
}

ARenderable* ARenderable::GetParent()
{
    return this->Parent;
}

void ARenderable::SetParent(ARenderable* object)
{
    if(this->Parent != NULL)
    {
        this->Parent->RemoveChild(this);
    }

    if(object == NULL)
    {
        // Detatch the object from its parent.
        this->Parent = NULL;
    }
    else
    {
        // Attach this object to a new parent.
        object->AddChild(this);

        // It is the parent's job to assign this object Parent variable
        assert(this->Parent == object);
    }
}

void ARenderable::AddChild(ARenderable* object)
{
    if(object != NULL)
    {
        this->Children->Add(object);

        object->Parent = this;
    }
}

void ARenderable::RemoveChild(ARenderable* object)
{
    if(object != NULL)
    {
        object->Parent = NULL;

        this->Children->RemoveObject(object);
    }
}

ArrayList<ARenderable*>* ARenderable::GetChildren()
{
    return this->Children;
}

void ARenderable::OnPreDraw()
{

}

void ARenderable::OnPostDraw()
{

}
