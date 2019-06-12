#pragma once

#include "core.h"
#include <Game/Game.h>

struct ENGINE_CLASS Tile
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

typedef ATexture** Tileset;

struct ENGINE_CLASS TilemapConfig
{
    int width;
    int height;

    Tileset tileset;
    int** tileData;
};

class ENGINE_CLASS Tilemap : public ARenderable
{
public:
    Tilemap(GameEngine* engine, TilemapConfig* config);
    ~Tilemap();

    int width;
    int height;
    Tile*** tiles;

    void Setup(ARenderer* renderer);

private:
    GameEngine* Engine;
};
