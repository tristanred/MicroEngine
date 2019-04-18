#include "Tilemap.h"

#include <ARenderable.h>

Tilemap::Tilemap(GameEngine* engine) : ARenderable(engine->Renderer)
{
    this->Engine = engine;
    
    this->width = 10;
    this->height = 10;

    tiles = new Tile**[this->width];
    for(int i = 0; i < this->width; i++)
    {
        tiles[i] = new Tile*[10];
        for(int k = 0; k < this->height; k++)
        {
            tiles[i][k] = new Tile();
        }
    }
}

Tilemap::~Tilemap()
{
}

void Tilemap::Setup(ARenderer* renderer)
{
    for(int i = 0; i < this->width; i++)
    {
        for(int k = 0; k < this->height; k++)
        {
            tiles[i][k]->tex = this->Engine->CreateSprite();
            tiles[i][k]->tex->SetTexture("tile_grass");
            
            //renderer->CreateTexture("tile_grass");
            tiles[i][k]->tex->SetSize(32, 32);
            tiles[i][k]->tex->SetPosition(i * 32, k * 32);
            
            this->AddChild(tiles[i][k]->tex);
        }
    }
}
