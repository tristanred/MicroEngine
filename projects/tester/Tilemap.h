#pragma once

#include <Game/Game.h>

struct Tile
{
    ASprite* tex;
};

class Tilemap : public ARenderable
{
public:
    Tilemap(GameEngine* engine);
    ~Tilemap();

    int width;
    int height;
    Tile*** tiles;

    void Setup(ARenderer* renderer);
    void Update(unsigned int deltaTime);
    
private:
    GameEngine* Engine;
};
