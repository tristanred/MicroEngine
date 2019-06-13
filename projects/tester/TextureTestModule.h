#pragma once

#include <GameModule.h>
#include <GameEngine.h>
#include <Rendering/ARenderer.h>
#include <Rendering/ASprite.h>
#include <Rendering/AText.h>
#include <Rendering/ATexture.h>
#include <Rendering/AFont.h>
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