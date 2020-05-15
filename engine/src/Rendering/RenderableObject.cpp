#include "Rendering/RenderableObject.h"

#include "GameEngine.h"
#include "Rendering/ATexture.h"


RenderableObject::RenderableObject(GameEngine* engine) : GameObject(engine)
{
    LogTrace("RenderableObject::RenderableObject");

    this->Renderer = engine->Renderer;

    this->Parent = NULL;
    this->Children = new ArrayList<RenderableObject*>();

    this->texture = NULL;

    this->size = FSize(0, 0);
    this->position = FPosition(0, 0);
    this->scale = vec2(1, 1);
    this->rotation = 0;
    this->PositionSystem = VIEWPORT_RELATIVE;
    this->isVisible = true;
}

RenderableObject::~RenderableObject()
{
    LogTrace("RenderableObject::~RenderableObject");

    if(this->texture != NULL)
    {
        this->Renderer->DeleteTexture(this->texture);
    }

    this->Parent = NULL;

    this->Children->DeleteElements();

    delete(this->Children);
    // TODO : Delete each children
}

void RenderableObject::Show(bool value)
{
    this->isVisible = value;
}

FRectangle RenderableObject::GetRectangle()
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

        myChildBounds.X += this->GetPosition().X;
        myChildBounds.Y += this->GetPosition().Y;

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
            myRect.Width = myChildBounds.Width;
        }
        if(myChildBounds.Bottom() > myRect.Bottom())
        {
            myRect.Height = myChildBounds.Height;
        }

        return myRect;
    }

    return FRectangle(this->position, this->size);
}

FPosition RenderableObject::GetPosition()
{
    if(this->Parent == NULL)
    {
        return this->position;
    }
    else
    {
        FPosition calculatedResult = this->position;

        if(this->Parent != NULL)
        {
            FPosition parentPos = this->Parent->GetPosition();
            calculatedResult.X *= this->Parent->GetScale().x;
            calculatedResult.Y *= this->Parent->GetScale().y;

            calculatedResult.X += parentPos.X;
            calculatedResult.Y += parentPos.Y;
        }

        return calculatedResult;
    }
}

void RenderableObject::SetPosition(FPosition position)
{
    this->position = position;
}

void RenderableObject::SetPosition(float x, float y)
{
    this->position.X = x;
    this->position.Y = y;
}

void RenderableObject::SetPositionAnchored(FPosition position, vec2 anchor)
{
    auto currentSize = this->GetSize();

    auto sizeOffset =
        vec2(currentSize.Width * anchor.x, currentSize.Height * anchor.y);

    FPosition newPos =
        FPosition(position.X - sizeOffset.x, position.Y - sizeOffset.y);

    this->SetPosition(newPos);
}

FSize RenderableObject::GetSize()
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

void RenderableObject::SetSize(FSize size)
{
    this->size = size;
}

void RenderableObject::SetSize(float w, float h)
{
    this->size.Width = w;
    this->size.Height = h;

    ATexture* textureToResize = this->GetTexture();
    if(textureToResize != NULL)
    {
        textureToResize->SetSize(this->size);
    }
}

FPolygon RenderableObject::GetPolygon()
{
    return this->GetRectangle().AsPolygon();
}

vec2 RenderableObject::GetScale()
{
    vec2 finalScale = this->scale;

    if(this->Parent != NULL)
    {
        vec2 parentScale = this->Parent->GetScale();
        finalScale.x *= parentScale.x;
        finalScale.y *= parentScale.y;
    }

    return finalScale;
}

void RenderableObject::SetScale(float scale)
{
    this->SetScale(scale, scale);
}

void RenderableObject::SetScale(float x, float y)
{
    this->SetScale(vec2(x, y));
}

void RenderableObject::SetScale(vec2 scale)
{
    this->scale = scale;
}

float RenderableObject::GetRotation()
{
    float finalRotation = this->rotation;

    if(this->Parent != NULL)
    {
        float parentRotation = this->Parent->GetRotation();
        finalRotation += parentRotation;
    }

    return finalRotation;
}

void RenderableObject::SetRotation(float angle)
{
    this->rotation = angle;
}

ATexture* RenderableObject::GetTexture()
{
    return this->texture;
}

void RenderableObject::SetTexture(const char* filepath)
{
    if(filepath != NULL)
    {
        ATexture* tex = this->Renderer->CreateTexture(filepath);

        this->SetTexture(tex);
    }
}

void RenderableObject::SetTexture(ATexture* newTexture)
{
    if(this->texture != NULL)
    {
        this->Renderer->DeleteTexture(this->texture);
    }

    this->texture = newTexture;

    this->size = this->texture->GetSize();
}

enum POSITION_SYSTEM RenderableObject::GetPositionSystem()
{
    return this->PositionSystem;
}

void RenderableObject::SetPositionSystem(enum POSITION_SYSTEM value)
{
    this->PositionSystem = value;
}

bool RenderableObject::IsVisible()
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
        RenderableObject* next = this->Parent;
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

RenderableObject* RenderableObject::GetParent()
{
    return this->Parent;
}

void RenderableObject::SetParent(RenderableObject* object)
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

void RenderableObject::AddChild(RenderableObject* object)
{
    if(object != NULL)
    {
        this->Children->Add(object);

        object->Parent = this;
    }
}

void RenderableObject::RemoveChild(RenderableObject* object)
{
    if(object != NULL)
    {
        object->Parent = NULL;

        this->Children->RemoveObject(object);
    }
}

ArrayList<RenderableObject*>* RenderableObject::GetChildren()
{
    return this->Children;
}

void RenderableObject::OnPreDraw() {}

void RenderableObject::OnPostDraw() {}
