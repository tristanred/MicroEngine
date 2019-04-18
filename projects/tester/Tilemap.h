#pragma once

#include <Game/Game.h>

struct Tile
{
    ASprite* tex;

    int tilemapPositionX;
    int tilemapPositionY;

    // Neighbor tiles, NULL if it is the edge.
    Tile* North;
    Tile* East;
    Tile* South;
    Tile* West;
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
