#include <Game/Tilemap.h>

#include <RenderableObject.h>

Tilemap::Tilemap(GameEngine* engine, TilemapConfig* config) : RenderableObject(engine)
{
    this->Engine = engine;
    
    this->width = 10;
    this->height = 10;

    tiles = new Tile**[this->width];
    for(int i = 0; i < this->width; i++)
    {
        tiles[i] = new Tile*[this->height];
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
            tiles[i][k]->tex->SetTexture("grass");
            tiles[i][k]->tilemapPositionX = i;
            tiles[i][k]->tilemapPositionY = k;

            if (i == 0)
            {
                tiles[i][k]->West = NULL;
            }
            else
            {
                tiles[i][k]->West = tiles[i - 1][k];
            }
            if (i == this->width - 1)
            {
                tiles[i][k]->East = NULL;
            }
            else
            {
                tiles[i][k]->East = tiles[i + 1][k];
            }
            if (k == 0)
            {
                tiles[i][k]->North = NULL;
            }
            else
            {
                tiles[i][k]->North = tiles[i][k - 1];
            }
            if (k == this->height - 1)
            {
                tiles[i][k]->South = NULL;
            }
            else
            {
                tiles[i][k]->South = tiles[i][k + 1];
            }

            //int w = tiles[i][k]->tex->GetSize().Width;
            //int h = tiles[i][k]->tex->GetSize().Height;
            float w = 32;
            float h = 32;
            tiles[i][k]->tex->SetSize(w, h);
            tiles[i][k]->tex->SetPosition((i * w), (k * h));
            
            this->AddChild(tiles[i][k]->tex);
        }
    }
}
