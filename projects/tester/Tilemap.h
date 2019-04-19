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

typedef ATexture** Tileset;

struct TilemapConfig
{
    int width;
    int height;

    Tileset tileset;
    int** tileData;
};

class Tilemap : public ARenderable
{
public:
    Tilemap(GameEngine* engine, TilemapConfig* config);
    ~Tilemap();

    int width;
    int height;
    Tile*** tiles;

    void Setup(ARenderer* renderer);
    void Update(unsigned int deltaTime);
    
private:
    GameEngine* Engine;
};
