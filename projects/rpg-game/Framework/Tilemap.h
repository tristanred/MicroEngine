#pragma once

class ARenderer;
class ATexture;
class Tile;

class Tilemap
{
public:
    Tilemap();
    ~Tilemap();
    
    const int textureCount = 3;
    ATexture* TileTextures[3];
    
    int rowCount;
    int colCount;
    Tile*** Tiles;
    
    void Setup(int columns, int rows, ARenderer* renderer);
    
    void Update(unsigned int deltaTime);
    void Draw(ARenderer* renderer);

};