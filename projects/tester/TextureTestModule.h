#pragma once

#include <Game/Game.h>

class TextureTestModule : public GameModule
{
public:
    TextureTestModule(GameEngine* engine);
    ~TextureTestModule();

    RenderableObject* Test;

    void Update(unsigned int deltaTime) override;
    void Draw(ARenderer* renderer) override;
};