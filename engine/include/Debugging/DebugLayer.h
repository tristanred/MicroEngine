#pragma once

class GameEngine;
class ATexture;
class ASprite;
class AText;
class AFont;
class ARenderer;

#include "core.h"
#include "libtech/geometry.h"

#define LAYERCOLOR 0x88000000

class ENGINE_CLASS DebugLayer
{
public:
    DebugLayer(GameEngine* engine);
    ~DebugLayer();

    ATexture* DebugDarkplate;
    AFont* DebugFont;
    AText* DeltaTimeText;

    AText* MouseWindowPositionLabel;
    AText* MouseWindowPositionValue;

    AText* MouseViewportPositionLabel;
    AText* MouseViewportPositionValue;

    void Show();
    void Hide();

    void Draw(ARenderer* renderer);
    void Update(unsigned int deltaTime);

    bool IsOpen();

private:
    GameEngine* engineRef;
    bool isVisible;

    FSize previousWindowSize;
};