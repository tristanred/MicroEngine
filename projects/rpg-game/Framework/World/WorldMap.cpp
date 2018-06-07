#include "WorldMap.h"

#include <microengine.h>
#include <TextureRepository.h>

WorldMap::WorldMap(GameModule* parent)
{
    this->MapTexture = parent->GetEngine()->TextureRepo->LoadFromFile("");
    this->MapTexture = parent->CreateTexture();
    this->MapTexture = parent->CreateTexture("filename.png");
    this->MapTexture->SetSolidColor(FSize(20, 20), 0xFFFFFFFF);

    this->MapImage = parent->CreateSprite();
}

WorldMap::~WorldMap()
{

}

void WorldMap::Draw(ARenderer* renderer)
{

}

void WorldMap::Update()
{

}
