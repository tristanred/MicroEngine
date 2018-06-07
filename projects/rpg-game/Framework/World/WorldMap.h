#pragma once

class GameEngine;
class GameModule;
class ARenderer;
class ASprite;
class ATexture;

class WorldMap
{
public:
    WorldMap(GameModule* parent);
    ~WorldMap();
    
    ATexture* MapTexture;
    ASprite* MapImage;
    
    void Draw(ARenderer* renderer);
    void Update();
};