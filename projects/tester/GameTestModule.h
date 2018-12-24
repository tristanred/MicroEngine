#pragma once

#include <GameModule.h>
#include <GameEngine.h>
#include <TextureRepository.h>

#include <ARenderer.h>
#include <ASprite.h>
#include <AText.h>
#include <ATexture.h>
#include <AFont.h>
#include <TickTimer.h>
#include <Controls/CButton.h>

#include <libtech/vec.h>

#include <stdint.h>

class GameTestModule : public GameModule
{
public:
    GameTestModule(GameEngine* engine);
    ~GameTestModule();

    ASprite* Box;
    ATexture* BoxTexture;
    AText* BoxText;
    AFont* ArialFont;
    vec2 boxVelocity;
    
    CButton* buttan;

    ASprite* clockSprite;

    AText* TimerText;
    TickTimer* timer;

    void Update(unsigned int deltaTime) override;
};
