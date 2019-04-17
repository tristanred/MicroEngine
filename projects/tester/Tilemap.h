#pragma once

#include <Game/Game.h>

struct Tile
{
    ATexture* tex;
    
    int x;
    int y;
    int w;
    int h;
};

class Tilemap
{
public:
    Tilemap();
    ~Tilemap();

    int width;
    int height;
    Tile*** tiles;


    void Setup(ARenderer* renderer);
    void Update(unsigned int deltaTime);
    void Draw(ARenderer* renderer);
};
