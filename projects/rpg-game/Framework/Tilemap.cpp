#include "Tilemap.h"

#include "microengine.h"
#include "Tile.h"
#include "libtech/randomgen.h"
#include "ARenderer.h"

Tilemap::Tilemap()
{
    Tiles = NULL;
    
    for(int i = 0; i < textureCount; i++)
    {
        TileTextures[i] = NULL;
    }
}

Tilemap::~Tilemap()
{
    for (int i = 0; i < this->rowCount; i++)
    {
        for (int k = 0; k < this->colCount; k++)
        {
            Tile* tile = Tiles[i][k];
            delete(tile);
        }

        delete(Tiles[i]);
    }

    delete(Tiles);
}

void Tilemap::Setup(int columns, int rows, ARenderer* renderer)
{
    TileTextures[0] = renderer->CreateTexture();
    TileTextures[0]->LoadFromFile("data/tile00.png");
    
    TileTextures[1] = renderer->CreateTexture();
    TileTextures[1]->LoadFromFile("data/tile01.png");
    
    TileTextures[2] = renderer->CreateTexture();
    TileTextures[2]->LoadFromFile("data/tile02.png");

    RandomGen rng;
    
    this->colCount = columns;
    this->rowCount = rows;
    
    Tiles = new Tile**[rowCount];
    
    for(int i = 0; i < rows; i++)
    {
        Tiles[i] = new Tile*[colCount];
        
        for(int k = 0; k < columns; k++)
        {
            Tile* newTile = new Tile();
            
            newTile->id = rng.GetRandom(3);
            
            Tiles[i][k] = newTile;
        }
    }
}

void Tilemap::Update(unsigned int deltaTime)
{
    
}

void Tilemap::Draw(ARenderer* renderer)
{
    for(int i = 0; i < this->rowCount; i++)
    {
        for(int k = 0; k < this->colCount; k++)
        {
            Tile* tile = Tiles[i][k];
            
            ATexture* tex = TileTextures[tile->id];
            
            FSize tsize = tex->GetSize();
            FPosition targetPos(k * tsize.Width, i * tsize.Height);
            renderer->DrawTexture(tex, targetPos.X, targetPos.Y);
        }
    }
}
