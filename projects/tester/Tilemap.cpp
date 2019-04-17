#include "Tilemap.h"

Tilemap::Tilemap()
{
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

void Tilemap::Setup(ARenderer* renderer)
{
    for(int i = 0; i < this->width; i++)
    {
        for(int k = 0; k < this->height; k++)
        {
            //tiles[i][k]->tex = renderer->CreateTexture("tile_grass");
            tiles[i][k]->w = 32;
            tiles[i][k]->h = 32;
            tiles[i][k]->x = i * tiles[i][k]->w;
            tiles[i][k]->y = k * tiles[i][k]->h;
            //tiles[i][k]->tex->SetSize(FSize(tiles[i][k]->w , tiles[i][k]->h));
        }
    }
}

void Tilemap::Draw(ARenderer* renderer)
{
    for(int i = 0; i < this->width; i++)
    {
        for(int k = 0; k < this->height; k++)
        {
            Tile* s = tiles[i][k];
            renderer->DrawTexture(s->tex, s->x, s->y);
        }
    }
}
