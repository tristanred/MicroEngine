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
    if(this->Parent == NULL)
    {
        return FRectangle(this->position, this->size);
    }
    else
    {
        return FRectangle(this->position, this->size); // TODO
    }
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

FSize ARenderable::GetSize()
{
    if(this->Parent == NULL)
    {
        return this->size;
    }
    else
    {
        return this->size; // TODO
    }
}

void ARenderable::SetSize(FSize size)
{
    this->size = size;
}

void ARenderable::SetSize(float w, float h)
{
    this->size.Width = w;
    this->size.Height = h;
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