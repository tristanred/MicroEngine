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

class TextureTestModule : public GameModule
{
public:
    TextureTestModule(GameEngine* engine);
    ~TextureTestModule();

    bool toggle;

    // Buncha'objects
    ATexture* TextureTest;
    AText* TextTest;
    ASprite* SpriteTest;

    void Update(unsigned int deltaTime) override;
    void Draw(ARenderer* renderer) override;
};