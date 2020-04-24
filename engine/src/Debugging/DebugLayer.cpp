#include "Debugging/DebugLayer.h"

#include "GameEngine.h"
#include "Input/AKeyboard.h"
#include "Input/AMouse.h"
#include "Rendering/AFont.h"
#include "Rendering/ARenderer.h"
#include "Rendering/ASprite.h"
#include "Rendering/AText.h"
#include "Rendering/ATexture.h"
#include "Viewport.h"
#include "libtech/geometry.h"

DebugLayer::DebugLayer(GameEngine* engine)
{
    engineRef = engine;

    DebugDarkplate = engine->CreateTexture();
    DebugDarkplate->SetSolidColor(
        FSize(engine->Renderer->GetWindowSize().Width, 200), LAYERCOLOR);

    DebugFont = engine->CreateTextFont();
    DebugFont->LoadFontFile("assets/engine/arial.ttf");

    MouseWindowPositionLabel = engine->CreateText();
    MouseWindowPositionLabel->SetFont(DebugFont);
    MouseWindowPositionLabel->SetText("MS AP:");
    MouseWindowPositionLabel->SetPosition(0, 0);
    MouseWindowPositionLabel->SetPositionSystem(VIEWPORT_STATIC);

    MouseWindowPositionValue = engine->CreateText();
    MouseWindowPositionValue->SetFont(DebugFont);
    MouseWindowPositionValue->SetText("?");
    MouseWindowPositionValue->SetPosition(
        MouseWindowPositionLabel->GetSize().Width + 5, 0);
    MouseWindowPositionValue->SetPositionSystem(VIEWPORT_STATIC);

    MouseViewportPositionLabel = engine->CreateText();
    MouseViewportPositionLabel->SetFont(DebugFont);
    MouseViewportPositionLabel->SetText("MS VP:");
    MouseViewportPositionLabel->SetPosition(0, 20);
    MouseViewportPositionLabel->SetPositionSystem(VIEWPORT_STATIC);

    MouseViewportPositionValue = engine->CreateText();
    MouseViewportPositionValue->SetFont(DebugFont);
    MouseViewportPositionValue->SetText("?");
    MouseViewportPositionValue->SetPosition(
        MouseViewportPositionLabel->GetSize().Width + 5, 20);
    MouseViewportPositionValue->SetPositionSystem(VIEWPORT_STATIC);

    this->isVisible = false;
}

DebugLayer::~DebugLayer()
{
    engineRef->ReleaseObject(DebugDarkplate);
    engineRef->ReleaseObject(DeltaTimeText);
}

void DebugLayer::Show()
{
    this->isVisible = true;
}

void DebugLayer::Hide()
{
    this->isVisible = false;
}

void DebugLayer::Draw(ARenderer* renderer)
{
    if(this->isVisible == false)
        return;

    // If the game was resized, resize our debug panel to fit the screen.
    if(previousWindowSize != renderer->GetWindowSize())
    {
        previousWindowSize = renderer->GetWindowSize();

        DebugDarkplate->SetSolidColor(
            FSize(renderer->GetWindowSize().Width, 200), LAYERCOLOR);
    }

    renderer->DrawTexture(DebugDarkplate, 0, 0);

    renderer->Draw(MouseWindowPositionLabel);
    renderer->Draw(MouseWindowPositionValue);

    renderer->Draw(MouseViewportPositionLabel);
    renderer->Draw(MouseViewportPositionValue);
}

void DebugLayer::Update(unsigned int deltaTime)
{
    vec2 absoluteMousePos = engineRef->Mouse->GetMousePosition();
    Viewport* viewport = engineRef->GetCurrentViewport();

    vec2 relativeMousePos = vec2();
    relativeMousePos.x = absoluteMousePos.x + viewport->CurrentView.X;
    relativeMousePos.y = absoluteMousePos.y + viewport->CurrentView.Y;

    char posText[64];
    sprintf(posText, "%d, %d", (int)absoluteMousePos.x,
            (int)absoluteMousePos.y);
    MouseWindowPositionValue->SetText(posText);

    sprintf(posText, "%d, %d", (int)relativeMousePos.x,
            (int)relativeMousePos.y);
    MouseViewportPositionValue->SetText(posText);
}

bool DebugLayer::IsOpen()
{
    return isVisible;
}
