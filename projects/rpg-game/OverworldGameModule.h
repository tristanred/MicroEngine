#pragma once

#include <GameModule.h>

class OverworldGameModule : public GameModule
{
public:
    explicit OverworldGameModule(GameEngine* engine);
    ~OverworldGameModule() override;

    void Update() override;

    void Draw(ARenderer *renderer) override;

private:
};


