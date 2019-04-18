#pragma once

#include <GameModule.h>
#include <GameEngine.h>
#include <ARenderer.h>
#include <ASprite.h>
#include <AText.h>
#include <ATexture.h>
#include <AFont.h>
#include <TickTimer.h>
#include <Controls/CButton.h>
#include <libtech/vec.h>
#include <stdint.h>

#include "DinoCharacter.h"
#include "Tilemap.h"

class GameTestModule : public GameModule
{
public:
    GameTestModule(GameEngine* engine);
    ~GameTestModule();

    ASprite* Box;
    ASprite* Box2;
    ATexture* BoxTexture;
    AText* BoxText;
    AFont* ArialFont;
    vec2 boxVelocity;

    CButton* buttan;

    ASprite* clockSprite;

    DinoCharacter* Dinono;

    AText* TimerText;
    TickTimer* timer;

    Tilemap* Map;

    void Update(unsigned int deltaTime) override;
};
